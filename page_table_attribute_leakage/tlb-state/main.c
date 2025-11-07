/* See LICENSE file for license and copyright information */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "ptedit_header.h"
#include "cacheutils.h"
#include "performance-counter.h"
#include "statistics.h"
#include "module/prefetch.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_WHITE   "\x1b[0m"

#define NUMBER_OF_MEASUREMENTS 1
#define TRIES 1000000
#define AVG 1

#define OUTLIER_THRESHOLD (5000*AVG)

typedef struct measurement_s {
  const char* name;
  ptedit_pte_t set;
  ptedit_pte_t unset;
  size_t memory_type;
} measurement_t;

#define PTEDIT_MT_DEFAULT -1

measurement_t measurements[] = {
  {
    .name = "Normal",
    .memory_type = PTEDIT_MT_WB,
    .set = {
      .present = 1
    }
  },
  {
    .name = "Not-User/Not-Accessed",
    .memory_type = PTEDIT_MT_WB,
    .unset = {
      .user_access = 1,
      .accessed = 1
    }
  },
  {
    .name = "Not-Accessed",
    .memory_type = PTEDIT_MT_WB,
    .unset = {
      .accessed = 1
    }
  },
  {
    .name = "Not-User",
    .memory_type = PTEDIT_MT_WB,
    .unset = {
      .user_access = 1
    }
  },
  {
    .name = "Not-Present",
    .memory_type = PTEDIT_MT_WB,
    .unset = {
      .present = 1
    }
  },
  {
    .name = "Not-Present/Not-User",
    .memory_type = PTEDIT_MT_WB,
    .unset = {
      .present = 1,
      .user_access = 1,
    }
  },
  {
    .name = "Read-Only (r--)",
    .memory_type = PTEDIT_MT_WB,
    .unset = {
      .writeable = 1,
      .execution_disabled = 1
    }
  },
  {
    .name = "Read-Exec (r-x)",
    .memory_type = PTEDIT_MT_WB,
    .unset = {
      .writeable = 1,
    }
  },
  {
    .name = "Read-Write (rw-)",
    .memory_type = PTEDIT_MT_WB,
    .unset = {
      .execution_disabled = 1
    }
  },
  {
    .name = "Not-Dirty",
    .memory_type = PTEDIT_MT_WB,
    .unset = {
      .dirty = 1
    }
  },
  {
    .name = "Not-User/Not-Accessed",
    .memory_type = PTEDIT_MT_WB,
    .unset = {
      .user_access = 1,
      .accessed = 1
    }
  },
  {
    .name = "Not-User/Not-Accessed/Not-Present",
    .memory_type = PTEDIT_MT_WB,
    .unset = {
      .user_access = 1,
      .accessed = 1,
      .present = 1
    }
  },
  {
    .name = "Write-Protected",
    .memory_type = PTEDIT_MT_WP,
  },
  {
    .name = "Uncachable",
    .memory_type = PTEDIT_MT_UC,
  }
};

inline __attribute__((always_inline)) void prefetch(size_t p) {
  asm volatile("mfence");
  asm volatile ("prefetcht2 (%0)" : : "r" (p));
  //asm volatile ("cldemote (%0)" : : "r" (p));
  asm volatile("mfence");
}

char __attribute__((aligned(4096))) buffer[4096*10];

void set_bits(void* address, measurement_t measurement, bool print)
{
  ptedit_entry_t entry = ptedit_resolve(address, 0);
  entry.valid = PTEDIT_VALID_MASK_PTE;

#define CHECK_AND_SET(x) \
  if (measurement.set.x == 1) { \
    ptedit_cast(entry.pte, ptedit_pte_t).x = 1; \
  } else if (measurement.unset.x == 1) { \
    ptedit_cast(entry.pte, ptedit_pte_t).x = 0; \
  }

  CHECK_AND_SET(present)
  CHECK_AND_SET(writeable)
  CHECK_AND_SET(user_access)
  CHECK_AND_SET(write_through)
  CHECK_AND_SET(cache_disabled)
  CHECK_AND_SET(accessed)
  CHECK_AND_SET(dirty)
  CHECK_AND_SET(size)
  CHECK_AND_SET(global)
  CHECK_AND_SET(execution_disabled)

  if (measurement.memory_type != PTEDIT_MT_DEFAULT) {
    int memory_type = ptedit_find_first_mt(measurement.memory_type);
    if (memory_type == -1) {
      fprintf(stdout, COLOR_RED "Error: Could not find MT for %zu\n" COLOR_RESET, measurement.memory_type);
    } else {
      entry.pte = ptedit_apply_mt(entry.pte, memory_type);
    }
  }

  /* Update */
  ptedit_update(address, 0, &entry);

  /* Debug print */
  if (print == true) {
    ptedit_print_entry(entry.pte);
  }
}

bool compare_bits(void* address, measurement_t measurement)
{
    ptedit_entry_t entry = ptedit_resolve((void*) address, 0);
    bool different = false;

#define COMPARE(x) \
  if (measurement.set.x == 1) { \
    if (ptedit_cast(entry.pte, ptedit_pte_t).x != 1) { \
      different = true; \
    } \
  } else if (measurement.unset.x == 1) { \
    if (ptedit_cast(entry.pte, ptedit_pte_t).x != 0) { \
      different = true; \
    } \
  }

  COMPARE(present)
  COMPARE(writeable)
  COMPARE(user_access)
  COMPARE(write_through)
  COMPARE(cache_disabled)
  COMPARE(accessed)
  COMPARE(dirty)
  COMPARE(size)
  COMPARE(global)
  COMPARE(execution_disabled)

  return different;
}

static float results[TRIES];
static performance_counter_group_values_t results_pc[TRIES];

// measure(buffer, NULL, true, &performance_counter_group, false, prefetch_fd);
// measure(buffer, &measurement, true, &performance_counter_group, true, prefetch_fd);
// measure(buffer, &measurement, false, &performance_counter_group, true, prefetch_fd);
size_t measure(void* addr, measurement_t* measurement, bool flushtlb, performance_counter_group_t* performance_counter_group, bool print, size_t pfd) {
  size_t address = (size_t) addr;
  bool different = false;
  uint64_t begin = 0, end = 0, min = 0, max = 0;

  // TRIES = 100000
  for (size_t i = 0; i < TRIES; i++) {
    if (measurement != NULL) {
      set_bits(addr, *measurement, false);
      if (measurement->unset.accessed == 0) {
	prefetch(address);
      }
    }

    /* Flush-TLB? */
    if (flushtlb == true) {
      ptedit_invalidate_tlb((void*) address);
    } else { // dont flush
      if (measurement->unset.accessed == 0) {
	prefetch(address);
      }
    }

    /* Read performance counter */
    performance_counter_group_values_t pc_begin;
    performance_counter_group_read(performance_counter_group, &pc_begin);

    //taehunk
    //results[i] = memaccesstime(address);
    //results[i] = memdemotetime(address);
    //
    begin = rdtsc();

    /* Prefetch kernel address */
    for(size_t j = 0; j < AVG; j++) {
        prefetch(address);
    }

    end = rdtsc();
    // taehunk
    if(end-begin > 300){
	    i--;
	    continue;
    }
    //printf("%d\n", end-begin);


    performance_counter_group_values_t pc_end;
    performance_counter_group_read(performance_counter_group, &pc_end);

    /* compare if different */
    if (measurement != NULL) {
      different = compare_bits((void*) address, *measurement);
    }

    performance_counter_group_values_t pc_diff = performance_counter_group_values_diff(performance_counter_group, pc_begin, pc_end);
    results[i] = (float) (end - begin);
    results_pc[i] = pc_diff;

    if(end - begin < min || !min) min = end - begin;
    if(end - begin > max) max = end - begin;
  }

  float average = 0, std_deviation = 0;
  size_t new_n = 0;
  compute_statistics(results, TRIES, &new_n, &average, NULL, &std_deviation, NULL);

  if (print == true) {
    printf("%s", flushtlb == true ? COLOR_RED : COLOR_GREEN);
    printf("  %6.f (sigma: %6.2f, min: %5zd, max: %8zd, n: %8zu)\n", average, std_deviation, min, max, new_n);
    printf("%s", COLOR_RESET);

    for (int i = 0; i < performance_counter_group->n; i++) {
      const char* name = performance_counter_group->counter[i].name;

      float average = 0, std_error = 0;
      performance_counter_group_compute_statistics(results_pc, TRIES, i, NULL, &average, NULL, NULL, &std_error);
      fprintf(stderr, "%s", COLOR_MAGENTA);
      fprintf(stderr, "%40s - %.2f (+- %.2f)\n", name, average, std_error);
      fprintf(stderr, "%s", COLOR_RESET);
    }

    if (different == true) {
      printf("%s", COLOR_YELLOW);
      printf("     PTE different");
      printf("%s\n", COLOR_RESET);
    }
  }

  return average;
}

#define LENGTH(x) (sizeof(x)/sizeof((x)[0]))

int main(int argc, char* argv[])
{

  /* Setup */
  if (ptedit_init()) {
    printf("Error: Could not initalize PTEditor, did you load the kernel module?\n");
    return 1;
  }

  size_t number_of_measurements = NUMBER_OF_MEASUREMENTS;

  /* Setup performance-counter */
  performance_counter_group_t performance_counter_group = performance_counter_group_init(getpid());
  performance_counter_group_add(&performance_counter_group, PERF_RAW_EVENT(0x08,0x01), "Page Table Walks (D-Side)");

  performance_counter_group_enable(&performance_counter_group);
  performance_counter_group_reset(&performance_counter_group);

  /* Initialize memory */
  memset(buffer, 0, 10*4096);

  int prefetch_fd = open("/dev/prefetch-profile", O_RDONLY);
  if (prefetch_fd < 0) {
    printf ("Error: Can't open device file: %s\n", "/dev/prefetch-profile");
    return -1;
  }

  /* Warmup */
  for (size_t i = 0; i < 5; i++) {
    measure(buffer, NULL, true, &performance_counter_group, false, prefetch_fd);
  }

  /* Get original entry */
  ptedit_entry_t entry = ptedit_resolve(buffer, 0);
  entry.valid = PTEDIT_VALID_MASK_PTE;
  ptedit_print_entry(entry.pte);

  /* Run measurements */
  for (size_t i = 0; i < LENGTH(measurements); i++) {
    measurement_t measurement = measurements[i];
    fprintf(stdout, COLOR_CYAN "Measurement: %s\n" COLOR_RESET, measurement.name);

    /* Restore entry */
    ptedit_update(buffer, 0, &entry);

    /* Set bits based on measurement */
    //set_bits(buffer, measurement, false);
    set_bits(buffer, measurement, true);

    /* Run measurement */
    for (size_t j = 0; j < number_of_measurements; j++) {
      measure(buffer, &measurement, true, &performance_counter_group, true, prefetch_fd);
    }

    for (size_t j = 0; j < number_of_measurements; j++) {
      measure(buffer, &measurement, false, &performance_counter_group, true, prefetch_fd);
    }
  }

  /* Restore entry */
  ptedit_update(buffer, 0, &entry);

  /* Clean-up */
  ptedit_cleanup();

  return 0;
}


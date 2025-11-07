#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "../ptedit_header.h"
#include "cacheutils.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RESET "\x1b[0m"

#define TAG_OK COLOR_GREEN "[+]" COLOR_RESET " "
#define TAG_FAIL COLOR_RED "[-]" COLOR_RESET " "
#define TAG_PROGRESS COLOR_YELLOW "[~]" COLOR_RESET " "

int main(int argc, char *argv[]) {
  char *pt;
  char *target = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  char *secret = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  memset(target, 'B', 4096);
  memset(secret, 'S', 4096);

  if (ptedit_init()) {
    printf(TAG_FAIL "Error: Could not initalize PTEditor, did you load the kernel module?\n");
    return 1;
  }

  ptedit_entry_t secret_entry = ptedit_resolve(secret, 0);

  /* "target" uses the manipulated page-table entry */
  ptedit_entry_t target_entry = ptedit_resolve(target, 0);
  ptedit_print_entry(target_entry.pte);
  printf("%llx\n", target);
  printf("%llx\n", &main);

  for(;;){
 // *target=0x12;
  //maccess(target);
  //prefetch(target);
  cldemote(target);

  //ptedit_invalidate_tlb(secret);
  }


  ptedit_cleanup();

  printf(TAG_OK "Done\n");
}

#include "cache/evchain.h"

void demote1_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
			 "cldemote 0(%%rcx)\n"
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}




void test1_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}


void test2_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}


void test3_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;" 
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}


void test4_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test5_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;" 
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test6_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;" 
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}


void test7_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;" 
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test8_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;" 
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test9_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test10_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 10
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}


void test11_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 10
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test12_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 10
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 12
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test13_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 10
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 12
                         "mfence;"
                         "movq (%%rcx), %%rcx;" 
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}


void test14_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 10
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 12
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 14
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test15_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 10
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 12
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 14
                         "mfence;"
                         "movq (%%rcx), %%rcx;" 
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test16_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 10
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 12
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 14
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 16
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test17_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 10
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 12
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 14
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 16
                         "mfence;"
                         "movq (%%rcx), %%rcx;" 
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test18_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 10
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 12
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 14
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 16
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 18
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test19_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 10
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 12
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 14
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 16
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 18
                         "mfence;"
                         "movq (%%rcx), %%rcx;" 
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test20_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 10
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 12
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 14
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 16
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 18
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 20
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test21_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 10
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 12
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 14
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 16
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 18
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 20
                         "mfence;"
                         "movq (%%rcx), %%rcx;" 
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}

void test22_evchain(evchain *ptr) {
    __asm__ __volatile__("mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 2
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 4
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 6
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 8
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 10
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 12
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 14
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 16
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 18
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 20
                         "mfence;"
                         "movq (%%rcx), %%rcx;"
                         "mfence;"
                         "movq (%%rcx), %%rcx;" // 22
                         "mfence;"
                         :
                         : "c"(ptr)
                         : "cc", "memory");
}





evchain *evchain_build(u8 *addrs[], size_t size) {
    size_t i;
    evchain *ptr, *next, *prev;

    if (size == 0) {
        return NULL;
    }

    for (i = 0; i < size; i++) {
        ptr = (evchain *)addrs[i];
        next = (evchain *)addrs[(i + 1) % size];
        if (i > 0) prev = (evchain *)addrs[i - 1];
        else prev = (evchain *)addrs[size - 1];

        ptr->next = next;
        ptr->prev = prev;
    }
    return (evchain *)addrs[0];
}

evchain *evchain_stride(u8 *start, ptrdiff_t stride, size_t size) {
    size_t i = 0;
    evchain *head = (evchain *)start, *cur = head, *next;
    if (size == 0 || stride < sizeof(evchain)) {
        return NULL;
    }

    for (i = 1; i < size; i++) {
        next = (evchain *)((u8 *)cur + stride);
        cur->next = next;
        next->prev = cur;
        cur = next;
    }

    cur->next = head;
    head->prev = cur;
    return head;
}

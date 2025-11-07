# Cache Demote for Fast Eviction Set Construction and Page-Table Attribute Leakage

## Overview
This repository contains artifacts for our paper, which investigates the security implications of Intel’s `cldemote` ISA extension.  
We show that `cldemote` can be exploited for (1) efficiently constructing eviction sets for non-inclusive last-level caches, and (2) revealing page table attributes (including TLB state, permission bits, and the page table level where translation terminates).

---

## More details

- **ESORICS 2025:** https://link.springer.com/chapter/10.1007/978-3-032-07894-0_15

## Experimental setup

- **Processors:** Intel 4th Gen Xeon Scalable Processors (Sapphire Rapids)  
    - `cldemote` is available on Sapphire Rapids, Emerald Rapids, Granite Rapids, and Sierra Forest.
- **OS / Kernel:** Ubuntu 24.04, Linux kernel 6.8.0-38

---

## Demo #1: Eviction set construction

- `eviction_set_construction/` — a demo for fast eviction set construction using the `cldemote` instruction.

This demo constructs eviction sets using the `cldemote` instruction. Since this method does not rely on a helper thread or cache conflicts, it is fast and efficient.  
We compare it with the helper thread-based method under two eviction-set construction algorithms: (1) the widely used baseline algorithm by Vila et al. [1], and (2) the Function-as-a-Service–oriented algorithm by Zhao et al. [2].

[1] Vila et al. “Theory and practice of finding eviction sets.” IEEE S&P 2019.  

[2] Zhao et al. “Last-level cache side channel attacks are feasible in the modern public cloud.” ASPLOS 2024.

## Demo #2: Page table attribute leakage

- `page_table_attribute_leakage/` — a demo for leaking page table attributes.

This demo leaks page table attributes such as TLB state, permission bits, and the page table level where address translation terminates.  
This attack shows that an unprivileged attacker can infer page table attributes of the kernel address space using the `cldemote` instruction.

## Disclaimer
This project is for educational and research purposes only. The use of this software to attack targets without prior mutual consent is strictly prohibited and illegal. The developer is not responsible for any damage caused by misuse of this exploit.


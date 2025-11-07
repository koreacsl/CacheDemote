# Paget able attribute leakage

## Usage

- `mapping-level_5level/` — distinguishing the page table level at which address translation terminates.

We prepare five distinct virtual addresses within an inaccessible kernel address space, where address translation for each address terminates at a different page-table level (i.e., PGD, P4D, PUD, PMD, and PT). 
We then measure the execution time of the `cldemote` instruction one million times.

```sh
$ make
$ ./profile
```

- `tlb-state/` — distinguishing TLB state (TLB hit vs. TLB miss).

We allocate a target page *P* and clear its user/supervisor bit to 0.
Subsequently, we measure the execution latency of the `cldemote` instruction one million times.
To induce a TLB hit, we execute `cldemote` twice consecutively. 
For the TLB-miss scenario, we flush the TLB before each measurement.

```sh
$ make
$ ./profile
```
## Referecne
Our implementaion was developed with reference to Lipp et al. [1]

[1] Lipp et al. "AMD prefetch attacks through power and time.", USENIX Security 2022.


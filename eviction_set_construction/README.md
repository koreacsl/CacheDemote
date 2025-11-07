# Fast and Efficient Eviction-Set Construction

## Usage

This program constructs a single eviction set on the directory (SF).

The program also takes the following optional arguments:

- `-A`: name of the eviction-set construction algorithm. It should be chosen from:
  - `vila`: eviction-set construction algorithm by Vila et al. [1]
  - `straw`: eviction-set construction algorithm by Zhao et al. [2]

```sh
$ make
$ ./osc-single-evset SF -A vila
```

## Referecne
Our implementaion was developed with reference to Zhao et al. [2].


[1] Vila et al. “Theory and practice of finding eviction sets.” IEEE S&P 2019.

[2] Zhao et al. “Last-level cache side channel attacks are feasible in the modern public cloud.” ASPLOS 2024.

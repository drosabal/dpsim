# dpsim

## Build

```sh
make
```

## Usage

```sh
./dpsim
```

### 1. Weighted approximate common substring

Given two input strings of characters A-Z, not necessarily of the same length, determines the best (largest score) common substring. The score that determines the best substring is the sum of the weights (w) for each matching character in the sequence minus a penalty (d) for each mismatch. The input strings are randomly generated with a given size.

### 2. Maximal square

Given an m x n boolean matrix B, finds the largest square k x k submatrix whose elements are all zeros.

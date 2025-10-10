# Range Generator

A simple arithmetic progression generator similar to Python's range().

## Usage

```bash
./range [M=0] N [S=1]
```

- No parameters — show help
- One parameter N — sequence [0, 1, … N-1]
- Two parameters M, N — sequence [M, M+1, … N-1]
- Three parameters M, N, S — sequence [M, M+S, M+2S, … N-1]

## Build and Test

```bash
make        # compile
make test   # run tests
make clean  # clean up
```

## Files

- `range.c` — source code
- `Makefile` — build and test
- `range1.gdb`, `range2.gdb` — gdb scripts
- `real-range-1`, `real-range-2` — reference outputs

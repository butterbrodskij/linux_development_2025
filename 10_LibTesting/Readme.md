# Growable Memory Buffers for C99

A lightweight C99 library providing dynamic, growable arrays with automatic memory management through intuitive macros. Originally by [Christopher Wellons](http://github.com/skeeto/growable-buf), packaged as a proper shared library with comprehensive testing.

## Features

- **Header-only macros** for intuitive API (`buf_push`, `buf_pop`, `buf_size`, etc.)
- **Automatic memory management** with exponential growth strategy
- **Type-safe operations** working with any data type
- **Zero dependencies** beyond standard C library
- **Thread-safe** (no global state)
- **Portable** C99 code

## API Overview

### Macros
```c
buf_size(v)      // Return number of elements (size_t)
buf_capacity(v)  // Return total capacity (size_t)
buf_free(v)      // Destroy and free buffer
buf_push(v, e)   // Append element e to end
buf_pop(v)       // Remove and return element from end
buf_grow(v, n)   // Increase capacity by n elements
buf_trunc(v, n)  // Set capacity to exactly n elements
buf_clear(v)     // Set size to 0 (keep capacity)
```

### Function
```c
void *buf_grow1(void *v, size_t esize, ptrdiff_t n);  // Internal growth function
```

## Build & Installation

### Using Autotools
```bash
# Standard build
autoreconf -fisv # Generate configure script
./configure
make

# With code coverage
./configure --enable-gcov
make
make check  # Run tests
make gcov   # View coverage report
```

### Direct Compilation
```bash
# Simple compile
gcc -std=c99 -I. -c libbuf.c -o libbuf.o

# Create shared library
gcc -std=c99 -shared -fPIC libbuf.c -o libbuf.so
```

## Testing

### Test Suite
```bash
make check  # Run all tests

# View test logs
make checklog
```

### Available Tests
- **Initialization**: Basic buffer creation and cleanup
- **Push/Pop Operations**: Element manipulation
- **Capacity Management**: Growth and truncation
- **Memory Failures**: Out-of-memory and overflow handling

## License

Public domain (as the original). See source files for details.


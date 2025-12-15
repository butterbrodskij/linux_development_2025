# Number Guesser Game

A command-line number guessing game that uses binary search algorithm to guess your number with minimal attempts.

## Features

- Full internationalization support (English/Russian)
- Flexible answer recognition (Yes/No in multiple languages)
- Standard autotools build system
- Roman numbers support
- Extensive documentation and man support

## Usage

### After Installation
```bash
# Run with Russian locale
make run-ru

# Run with English locale  
make run-en

# Run with Russian locale and Roman numbers
make run-ru-r

# Run with English locale and Roman numbers
make run-en-r

# Or run directly
LANG=ru_RU.UTF-8 LC_ALL=ru_RU.UTF-8 /path/to/guesser
/path/to/guesser

# Start server with doxygen documentation
make http

# View manual page
MANPATH=$MANPATH:./doxygen-doc/man/ man guesser
```

### Game Play
```
guess a number from 1 to 3999
is your number greater than 2000? (Yes/No)
> no
is your number greater than 1000? (Yes/No)  
> no
is your number greater than 500? (Yes/No)
> no
...
your number: 69
```

## Supported Answers

The game recognizes multiple answer formats:

- **English**: `yes`, `y`, `no`, `n`
- **Russian**: `да`, `д`, `нет`, `н`

## Build and Install

### Standard Build
```bash
# Generate configure script
autoreconf -fisv

# Configure and build
./configure --prefix /tmp && make install

# Run installed version
make run-ru

# Get help
/path/to/guesser -h
```

### Development Commands
```bash
# Quick testing
make run-ru          # Build and run with Russian locale
make run-en          # Build and run with English locale

# Cleanup
make maintainer-clean  # Remove all generated files
```

## Internationalization

The game uses GNU gettext for translations:

- **Original strings** in source code wrapped with `_()`
- **Translation files** in `po/` directory
- **Automatic locale detection** based on system settings

## Error Handling

- **Invalid answers**: Prompts again with error message
- **EOF (Ctrl+D)**: Graceful exit with error message

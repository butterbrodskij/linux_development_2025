# File Move Utility

A secure file moving utility with comprehensive error handling and protection features.

## Usage

```bash
./move infile outfile
```

Moves contents from `infile` to `outfile` (overwriting if exists) and deletes `infile` upon success.

## Examples

```bash
# Basic file move
./move source.txt destination.txt

# Move with protection (files containing "PROTECT" in name won't be deleted)
LD_PRELOAD=./protect.so ./move PROTECT-data.txt backup.txt
```

## Build and Test

```bash
make        # compile move and protect.so
make test   # run all tests (error injection, normal operation, protection)
make clean  # remove generated files
```

## Test Categories

- **Error Injection Tests**: Simulate system call failures using strace
- **Normal Operation**: Verify correct file moving behavior  
- **Protection Tests**: Ensure PROTECT files are preserved with LD_PRELOAD

## Protection Library

The `protect.so` library prevents deletion of files containing "PROTECT" in their filename when loaded via `LD_PRELOAD`:

```bash
# Protected file won't be deleted
LD_PRELOAD=./protect.so ./move important-PROTECT-file.txt copy.txt

# Regular files are moved normally
LD_PRELOAD=./protect.so ./move regular-file.txt new-location.txt
```

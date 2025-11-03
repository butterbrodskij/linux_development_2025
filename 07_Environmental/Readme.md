# Hasher REPL Utility

A command-line utility for computing file and string hashes with interactive REPL interface and multiple output formats.

## Usage

```bash
./rhasher
```

Starts an interactive hashing session. Type commands or use Ctrl+D to exit.

## Command Syntax

```
<algorithm> <target>
```

- **algorithm**: Hash algorithm (MD5, SHA1, TTH) - case determines output format
- **target**: File path or quoted string starting with `"`

## Examples

```bash
# Interactive mode
./rhasher
> MD5 "hello_world         # Hex output (uppercase algorithm)
> md5 "hello_world         # Base64 output (lowercase algorithm)  
> SHA1 document.pdf        # File hashing
> sha1 document.pdf        # File hashing in Base64

# Non-interactive (pipes/redirection)
echo 'MD5 "test' | ./rhasher
echo "SHA1 file.txt" | ./rhasher
./rhasher < commands.txt
```

## Supported Algorithms

- **MD5** - 128-bit hash
- **SHA1** - 160-bit hash  
- **TTH** - Tiger Tree Hash

## Output Formats

- **Uppercase algorithms** (MD5, SHA1, TTH) → Hexadecimal output
- **Lowercase algorithms** (md5, sha1, tth) → Base64 output

## Build and Test

```bash
# Generate configure script
autoreconf -fisv

# Standard build (without readline)
./configure && make

# Build with readline support
./configure --with-readline && make

# Make test scripts executable if needed
chmod +x md5_tests.sh sha1_tests.sh error_tests.sh

# Run tests
make check

# Full cleanup (including autotools generated files)
make maintainer-clean
```

## Test Categories

- **MD5 Tests**: File and string hashing in hex and Base64
- **SHA1 Tests**: File and string hashing in hex and Base64  
- **Error Tests**: Invalid commands, missing files, unknown algorithms

# Regex Substitution Tool

A C implementation of regex substitution similar to `sed -E 's/regexp/substitution/'`.

## Usage

```bash
./esub regexp substitution string
```

Prints the result of replacing the first regexp match in `string` with `substitution`.

## Features

- Extended regular expressions (like `sed -E`)
- Group references `\0`-`\9` in substitution
- Error handling for invalid regex and group numbers
- Memory-safe dynamic buffer allocation

## Examples

```bash
# Simple substitution
./esub "abc" "XYZ" "test abc def"        # test XYZ def

# Group references  
./esub "([0-9]+)-([0-9]+)" "\2-\1" "123-456"  # 456-123

# Complex pattern
./esub "([[:digit:]]{4}) +([[:digit:]]{1,2}) +([[:alpha:]]+) +([[:alpha:]]+)" \
       "\4, \2 \3 year of \1" \
       "current date: 2024 17 October Thursday"
# current date: Thursday, 17 October year of 2024
```

## Build and Test

```bash
make        # compile
make test   # run comparison test with sed
make check  # run various test cases
make clean  # clean up
```

## Error Handling

- Invalid regex: `failed to compile regular expression: ...`
- Invalid group number: `unexpected window number: N`
- Memory allocation: `failed to allocate enough memory`

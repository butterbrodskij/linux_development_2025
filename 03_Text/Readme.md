# Randomize ASCII Art

A script for animated display of ASCII art character by character in random order.

## Usage

```bash
./randomize.sh [delay] < file.txt
cat file.txt | ./randomize.sh [delay]
```
- delay - optional parameter, time in seconds between characters (default: 0.1)

## Examples

```bash
LC_ALL=C cal | dash randomize.sh 0.05
dash randomize.sh 0.01 < randomize.sh
```

## Features

- Characters displayed in random order
- Spaces are skipped  
- Proper terminal positioning
- Compatible with /bin/dash
- Optimized for ASCII characters
- Basic Cyrillic support

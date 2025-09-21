# Terminal File Viewer (Show)

A simple terminal-based file viewer built with ncurses library. Displays text files with smooth scrolling and navigation.

## Features

- View text files of any size with efficient memory usage
- Display files in a bordered window with filename header
- Navigation:
  - `Space` - Scroll down one line
  - `↑/↓` - Scroll line by line
  - `←/→` - Horizontal scrolling for long lines
  - `PgUp/PgDn` - Page-by-page navigation
  - `ESC` - Exit program
- Handles long lines with horizontal scrolling
- Progressive loading for large files

## Building

```bash
make
```

## Usage

```bash
./Show filename.txt
```

## Cleanup

```bash
make clean
```

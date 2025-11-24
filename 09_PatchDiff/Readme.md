# Maze Generator

A C program that generates random passable mazes using Prim's algorithm with customizable size, symbols, and seed for reproducibility.

## Features

- Generates random perfect mazes (exactly one path between any two rooms)
- Configurable maze size (N×N rooms)
- Customizable wall and passage symbols
- Seed-based generation for reproducible results
- Guaranteed passability from any room to any other
- Walls occupy at least 15% of the maze

## Output Format

Mazes are represented as ASCII grids where:
- Each "room" is a 3×3 character cell
- Rooms are connected by breaking down walls
- Example 6×6 closed maze structure:
```
#############
#.#.#.#.#.#.#
#############
#.#.#.#.#.#.#
#############
#.#.#.#.#.#.#
#############
#.#.#.#.#.#.#
#############
#.#.#.#.#.#.#
#############
#.#.#.#.#.#.#
#############
```

## Usage

### Basic Usage
```bash
# Generate 6x6 maze with default symbols (# and .)
./lab0

# Generate 8x8 maze
./lab1 8

# Generate 5x5 maze with custom symbols (space and @)
./lab2 ' @' 5

# Generate reproducible 4x4 maze with seed 12
./lab3 12 '.#' 4

# Generate different 4x4 maze with seed 11
./lab3 11 '.#' 4
```

### Parameter Order
- **lab0**: No parameters (fixed 6×6)
- **lab1**: `[size]`
- **lab2**: `[symbols] [size]` 
- **lab3**: `[seed] [symbols] [size]`

Where:
- `size`: Number of rooms per side (N for N×N maze)
- `symbols`: Two characters: passage_symbol wall_symbol
- `seed`: Integer for reproducible random generation

## Build System

### Available Targets
```bash
make all          # Build all four versions (lab0-lab3)
make clean        # Remove all generated files
make run          # Build and test all versions with sample parameters

# Build specific version
make lab0
make lab1
make lab2
make lab3
```

### Generated Versions
- **lab0**: Original fixed-size version
- **lab1**: Adds configurable maze size
- **lab2**: Adds custom wall/passage symbols  
- **lab3**: Adds seed for reproducible generation

## Examples

### Sample Output
```
#############
#.......#...#
#######.#.#.#
#...#...#.#.#
#.###.###.#.#
#...#.....#.#
###.#######.#
#.......#...#
#.#######.###
#...#.....#.#
#.#.#.#####.#
#.#.........#
#############
```

### Testing
```bash
# Run all test cases
make run

# Expected output: Six different mazes from various configurations
# - Default 6x6 maze
# - 8x8 maze  
# - 5x5 maze with custom symbols
# - Three 4x4 mazes (two identical due to same seed)
```
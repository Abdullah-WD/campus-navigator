# Campus Navigator — Shortest Path Finder

A console-based route planner that models a campus (or any location network) as a
weighted graph and finds the shortest path between two points using **Dijkstra's
Algorithm**. Built in modern C++17 with a clean, modular structure.

## Why this project

This project is designed to demonstrate core **Data Structures & Algorithms** skills
in a real, usable form rather than an isolated leetcode-style script:

| DSA Concept | Where it's used |
|---|---|
| Graph (Adjacency List) | `Graph` class — locations as nodes, paths as weighted edges |
| Priority Queue (Min-Heap) | `shortestPath()` — Dijkstra's algorithm |
| Hash Map | `unordered_map` for O(1) name ↔ id lookups |
| BFS (Breadth-First Search) | `hopCount()` / `isReachable()` |
| DFS (Depth-First Search) | `isFullyConnected()` |
| File I/O & Parsing | `loadFromFile()` / `saveToFile()` (CSV-style persistence) |

## Features

- Add / remove locations and paths dynamically
- Find the shortest route between any two locations (with total distance)
- Check reachability and minimum hop count between two points
- Verify whether the whole map is connected
- Load a ready-made sample campus map to try instantly
- Save the current map to a CSV file for persistence

## Project Structure

```
campus-navigator/
├── include/
│   └── Graph.h        # Graph class declaration
├── src/
│   ├── Graph.cpp       # Dijkstra, BFS, DFS implementation
│   └── main.cpp        # Interactive CLI
├── Makefile
└── README.md
```

## Build & Run

```bash
make          # compiles to ./campus_navigator
make run      # build + run
make clean    # remove binary and generated files
```

Or manually:
```bash
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude src/main.cpp src/Graph.cpp -o campus_navigator
./campus_navigator
```

## Example

```
Choose an option: 7
Sample campus data loaded (7 locations).

Choose an option: 3
Source: Main Gate
Destination: Sports Complex
Shortest distance: 570m
Route: Main Gate -> Admin Block -> Library -> CS Department -> Sports Complex
```

## Possible Extensions

- Swap Dijkstra for A* using coordinates + heuristic
- Add a GUI/web front-end that consumes the same `Graph` engine
- Multi-criteria routing (shortest distance vs. fewest turns)

## Author

Abdullah Zafar — BSIT

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

## Example Output

Full session using the built-in sample data, showing the map, a shortest-path
query, a reachability check, and a connectivity check:

```
Campus Navigator — Shortest Path Finder
A DSA-driven route planner using Graphs, Dijkstra's Algorithm, and BFS/DFS.

========= Campus Navigator =========
 1. Add location
 2. Add path between two locations
 3. Find shortest path (Dijkstra)
 4. Check reachability + hop count (BFS)
 5. Check if whole map is connected (DFS)
 6. Show full map
 7. Load sample campus data
 8. Save map to file
 0. Exit
Choose an option: 7
Sample campus data loaded (7 locations).

Choose an option: 6

===== Campus Map (7 locations) =====
 Main Gate:
    -> Admin Block (120m)
 Admin Block:
    -> Main Gate (120m)
    -> Library (90m)
    -> Cafeteria (150m)
 Library:
    -> Admin Block (90m)
    -> CS Department (60m)
    -> Hostel Block (250m)
 Cafeteria:
    -> Admin Block (150m)
    -> CS Department (100m)
 CS Department:
    -> Library (60m)
    -> Cafeteria (100m)
    -> Sports Complex (300m)
 Hostel Block:
    -> Library (250m)
    -> Sports Complex (200m)
 Sports Complex:
    -> CS Department (300m)
    -> Hostel Block (200m)
==============================================

Choose an option: 3
Source: Main Gate
Destination: Sports Complex
Shortest distance: 570m
Route: Main Gate -> Admin Block -> Library -> CS Department -> Sports Complex

Choose an option: 4
Source: Main Gate
Destination: Hostel Block
Reachable in 3 hop(s).

Choose an option: 5
The map is fully connected.

Choose an option: 0
Goodbye!
```

## Possible Extensions

- Swap Dijkstra for A* using coordinates + heuristic
- Add a GUI/web front-end that consumes the same `Graph` engine
- Multi-criteria routing (shortest distance vs. fewest turns)

## Author

Abdullah Zafar — BSIT

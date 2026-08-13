#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <limits>

// Represents a weighted, undirected edge to a neighboring location
struct Edge {
    int destination;
    double weight; // distance in meters (or any unit)
};

// Result of a shortest-path query
struct PathResult {
    bool found = false;
    double totalDistance = 0.0;
    std::vector<int> pathNodeIds;
};

/*
 * Graph
 * -----
 * A weighted, undirected graph implemented with an adjacency list.
 * Used to model a campus (or any location network) where nodes are
 * places (e.g. "Library", "Cafeteria") and edges are walkable paths
 * with a distance/weight.
 *
 * Core DSA concepts demonstrated:
 *   - Adjacency list graph representation (HashMap of vectors)
 *   - Dijkstra's algorithm using a min-priority-queue
 *   - Breadth-First Search (BFS) for reachability / hop-count queries
 *   - Depth-First Search (DFS) for connectivity checks & cycle detection
 */
class Graph {
public:
    // Adds a new named location; returns its internal node id.
    // If the name already exists, returns the existing id.
    int addLocation(const std::string& name);

    // Removes a location and all edges connected to it.
    bool removeLocation(const std::string& name);

    // Adds a bidirectional weighted edge between two locations.
    // Creates the locations if they do not already exist.
    bool addPath(const std::string& from, const std::string& to, double weight);

    // Removes the edge between two locations (both directions).
    bool removePath(const std::string& from, const std::string& to);

    // Runs Dijkstra's algorithm from `source` to `target`.
    // Returns the shortest path (by total weight) and its distance.
    PathResult shortestPath(const std::string& source, const std::string& target) const;

    // Returns true if `target` is reachable from `source` (BFS).
    bool isReachable(const std::string& source, const std::string& target) const;

    // Returns the minimum number of hops (edges) between two locations (BFS).
    int hopCount(const std::string& source, const std::string& target) const;

    // Returns true if the entire graph is connected (DFS from any node).
    bool isFullyConnected() const;

    // Prints an adjacency-list style overview of the whole map.
    void printMap() const;

    // Prints a human-readable path (e.g. "Gate -> Library -> Cafeteria (250m)")
    void printPath(const PathResult& result) const;

    // Number of locations currently stored.
    size_t locationCount() const { return idToName.size(); }

    // Loads a set of edges from a simple CSV-like text file:
    //   from,to,weight
    // Returns number of edges successfully loaded.
    int loadFromFile(const std::string& filepath);

    // Saves the current graph to a CSV-like text file.
    bool saveToFile(const std::string& filepath) const;

private:
    std::unordered_map<std::string, int> nameToId;
    std::unordered_map<int, std::string> idToName;
    std::unordered_map<int, std::vector<Edge>> adjacency;
    int nextId = 0;

    int getIdOrThrow(const std::string& name, bool& ok) const;
};

#endif // GRAPH_H

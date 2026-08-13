#include "Graph.h"
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>

int Graph::addLocation(const std::string& name) {
    auto it = nameToId.find(name);
    if (it != nameToId.end()) return it->second;

    int id = nextId++;
    nameToId[name] = id;
    idToName[id] = name;
    adjacency[id] = {};
    return id;
}

bool Graph::removeLocation(const std::string& name) {
    auto it = nameToId.find(name);
    if (it == nameToId.end()) return false;

    int id = it->second;

    // Remove all edges pointing to this node from its neighbors
    for (auto& [otherId, edges] : adjacency) {
        edges.erase(std::remove_if(edges.begin(), edges.end(),
                        [id](const Edge& e) { return e.destination == id; }),
                    edges.end());
    }

    adjacency.erase(id);
    idToName.erase(id);
    nameToId.erase(it);
    return true;
}

bool Graph::addPath(const std::string& from, const std::string& to, double weight) {
    if (weight < 0) return false;
    int a = addLocation(from);
    int b = addLocation(to);

    adjacency[a].push_back({b, weight});
    adjacency[b].push_back({a, weight});
    return true;
}

bool Graph::removePath(const std::string& from, const std::string& to) {
    auto itA = nameToId.find(from);
    auto itB = nameToId.find(to);
    if (itA == nameToId.end() || itB == nameToId.end()) return false;

    int a = itA->second, b = itB->second;
    auto& edgesA = adjacency[a];
    auto& edgesB = adjacency[b];

    edgesA.erase(std::remove_if(edgesA.begin(), edgesA.end(),
                    [b](const Edge& e) { return e.destination == b; }),
                 edgesA.end());
    edgesB.erase(std::remove_if(edgesB.begin(), edgesB.end(),
                    [a](const Edge& e) { return e.destination == a; }),
                 edgesB.end());
    return true;
}

int Graph::getIdOrThrow(const std::string& name, bool& ok) const {
    auto it = nameToId.find(name);
    if (it == nameToId.end()) { ok = false; return -1; }
    ok = true;
    return it->second;
}

PathResult Graph::shortestPath(const std::string& source, const std::string& target) const {
    PathResult result;
    bool ok1, ok2;
    int src = getIdOrThrow(source, ok1);
    int dst = getIdOrThrow(target, ok2);
    if (!ok1 || !ok2) return result; // not found

    std::unordered_map<int, double> dist;
    std::unordered_map<int, int> prev;
    for (const auto& [id, _] : idToName) dist[id] = std::numeric_limits<double>::infinity();
    dist[src] = 0.0;

    // Min-heap of (distance, nodeId)
    using PQItem = std::pair<double, int>;
    std::priority_queue<PQItem, std::vector<PQItem>, std::greater<>> pq;
    pq.push({0.0, src});

    std::unordered_set<int> visited;

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (visited.count(u)) continue;
        visited.insert(u);
        if (u == dst) break;

        auto it = adjacency.find(u);
        if (it == adjacency.end()) continue;

        for (const Edge& e : it->second) {
            double newDist = d + e.weight;
            if (newDist < dist[e.destination]) {
                dist[e.destination] = newDist;
                prev[e.destination] = u;
                pq.push({newDist, e.destination});
            }
        }
    }

    if (dist[dst] == std::numeric_limits<double>::infinity()) {
        return result; // unreachable
    }

    // Reconstruct path by walking `prev` backwards
    std::vector<int> path;
    int cur = dst;
    path.push_back(cur);
    while (cur != src) {
        cur = prev[cur];
        path.push_back(cur);
    }
    std::reverse(path.begin(), path.end());

    result.found = true;
    result.totalDistance = dist[dst];
    result.pathNodeIds = path;
    return result;
}

bool Graph::isReachable(const std::string& source, const std::string& target) const {
    return hopCount(source, target) != -1;
}

int Graph::hopCount(const std::string& source, const std::string& target) const {
    bool ok1, ok2;
    int src = getIdOrThrow(source, ok1);
    int dst = getIdOrThrow(target, ok2);
    if (!ok1 || !ok2) return -1;
    if (src == dst) return 0;

    std::unordered_map<int, int> depth;
    std::queue<int> q;
    q.push(src);
    depth[src] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        auto it = adjacency.find(u);
        if (it == adjacency.end()) continue;

        for (const Edge& e : it->second) {
            if (!depth.count(e.destination)) {
                depth[e.destination] = depth[u] + 1;
                if (e.destination == dst) return depth[e.destination];
                q.push(e.destination);
            }
        }
    }
    return -1; // unreachable
}

bool Graph::isFullyConnected() const {
    if (idToName.empty()) return true;

    std::unordered_set<int> visited;
    std::vector<int> stack;
    int start = idToName.begin()->first;
    stack.push_back(start);

    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        if (visited.count(u)) continue;
        visited.insert(u);

        auto it = adjacency.find(u);
        if (it == adjacency.end()) continue;
        for (const Edge& e : it->second) {
            if (!visited.count(e.destination)) stack.push_back(e.destination);
        }
    }

    return visited.size() == idToName.size();
}

void Graph::printMap() const {
    std::cout << "\n===== Campus Map (" << idToName.size() << " locations) =====\n";
    for (const auto& [id, name] : idToName) {
        std::cout << " " << name << ":\n";
        for (const Edge& e : adjacency.at(id)) {
            std::cout << "    -> " << idToName.at(e.destination)
                      << " (" << e.weight << "m)\n";
        }
    }
    std::cout << "==============================================\n";
}

void Graph::printPath(const PathResult& result) const {
    if (!result.found) {
        std::cout << "No path found.\n";
        return;
    }
    std::cout << "Shortest distance: " << result.totalDistance << "m\n";
    std::cout << "Route: ";
    for (size_t i = 0; i < result.pathNodeIds.size(); ++i) {
        std::cout << idToName.at(result.pathNodeIds[i]);
        if (i + 1 < result.pathNodeIds.size()) std::cout << " -> ";
    }
    std::cout << "\n";
}

int Graph::loadFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return 0;

    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::stringstream ss(line);
        std::string from, to, weightStr;
        if (std::getline(ss, from, ',') &&
            std::getline(ss, to, ',') &&
            std::getline(ss, weightStr, ',')) {
            try {
                double w = std::stod(weightStr);
                if (addPath(from, to, w)) count++;
            } catch (...) {
                // skip malformed line
            }
        }
    }
    return count;
}

bool Graph::saveToFile(const std::string& filepath) const {
    std::ofstream file(filepath);
    if (!file.is_open()) return false;

    file << "# from,to,weight\n";
    std::unordered_set<long long> written;
    for (const auto& [id, edges] : adjacency) {
        for (const Edge& e : edges) {
            long long key = (id < e.destination)
                ? (static_cast<long long>(id) << 32) | e.destination
                : (static_cast<long long>(e.destination) << 32) | id;
            if (written.count(key)) continue;
            written.insert(key);
            file << idToName.at(id) << "," << idToName.at(e.destination) << "," << e.weight << "\n";
        }
    }
    return true;
}

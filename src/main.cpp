#include "Graph.h"
#include <iostream>
#include <limits>

static void printMenu() {
    std::cout << "\n========= Campus Navigator =========\n"
              << " 1. Add location\n"
              << " 2. Add path between two locations\n"
              << " 3. Find shortest path (Dijkstra)\n"
              << " 4. Check reachability + hop count (BFS)\n"
              << " 5. Check if whole map is connected (DFS)\n"
              << " 6. Show full map\n"
              << " 7. Load sample campus data\n"
              << " 8. Save map to file\n"
              << " 0. Exit\n"
              << "Choose an option: ";
}

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Graph campus;
    int choice = -1;

    std::cout << "Campus Navigator — Shortest Path Finder\n"
              << "A DSA-driven route planner using Graphs, Dijkstra's Algorithm, and BFS/DFS.\n";

    while (true) {
        printMenu();
        if (!(std::cin >> choice)) {
            clearInput();
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1: {
                std::cout << "Location name: ";
                std::string name;
                clearInput();
                std::getline(std::cin, name);
                campus.addLocation(name);
                std::cout << "Added \"" << name << "\".\n";
                break;
            }
            case 2: {
                std::string from, to;
                double weight;
                clearInput();
                std::cout << "From: ";
                std::getline(std::cin, from);
                std::cout << "To: ";
                std::getline(std::cin, to);
                std::cout << "Distance (meters): ";
                std::cin >> weight;
                if (campus.addPath(from, to, weight))
                    std::cout << "Path added: " << from << " <-> " << to << " (" << weight << "m)\n";
                else
                    std::cout << "Failed to add path (invalid weight).\n";
                break;
            }
            case 3: {
                std::string from, to;
                clearInput();
                std::cout << "Source: ";
                std::getline(std::cin, from);
                std::cout << "Destination: ";
                std::getline(std::cin, to);
                PathResult result = campus.shortestPath(from, to);
                campus.printPath(result);
                break;
            }
            case 4: {
                std::string from, to;
                clearInput();
                std::cout << "Source: ";
                std::getline(std::cin, from);
                std::cout << "Destination: ";
                std::getline(std::cin, to);
                int hops = campus.hopCount(from, to);
                if (hops == -1) std::cout << "Not reachable.\n";
                else std::cout << "Reachable in " << hops << " hop(s).\n";
                break;
            }
            case 5: {
                std::cout << (campus.isFullyConnected()
                    ? "The map is fully connected.\n"
                    : "The map has disconnected areas.\n");
                break;
            }
            case 6: {
                campus.printMap();
                break;
            }
            case 7: {
                campus.addPath("Main Gate", "Admin Block", 120);
                campus.addPath("Admin Block", "Library", 90);
                campus.addPath("Admin Block", "Cafeteria", 150);
                campus.addPath("Library", "CS Department", 60);
                campus.addPath("Cafeteria", "CS Department", 100);
                campus.addPath("CS Department", "Sports Complex", 300);
                campus.addPath("Library", "Hostel Block", 250);
                campus.addPath("Hostel Block", "Sports Complex", 200);
                std::cout << "Sample campus data loaded (" << campus.locationCount() << " locations).\n";
                break;
            }
            case 8: {
                std::string path = "campus_map.csv";
                if (campus.saveToFile(path))
                    std::cout << "Map saved to " << path << "\n";
                else
                    std::cout << "Failed to save map.\n";
                break;
            }
            default:
                std::cout << "Unknown option.\n";
        }
    }

    return 0;
}

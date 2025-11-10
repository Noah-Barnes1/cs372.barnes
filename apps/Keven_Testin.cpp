#include <iostream>
#include <vector>
#include "AdjListGraph.hpp"
#include "SocialUtils.h"

int main() {
    using G = AdjListGraph<int>;

    // Create 20 people labeled 0..19
    std::vector<int> people;
    for (int i = 0; i < 20; ++i) people.push_back(i);

    // We'll pick:
    // - you = 0
    // - kevin = 6
    //
    // Build an undirected "social" graph by adding both directions for each friendship.
    std::vector<std::pair<int, int>> edges;

    auto addFriendship = [&](int a, int b) {
        edges.emplace_back(a, b);
        edges.emplace_back(b, a);
        };

    addFriendship(0, 1);
    addFriendship(0, 2); // this creates a 0 -> 2 -> 6 path
    addFriendship(0, 3);

    addFriendship(1, 4);
    addFriendship(1, 5);

    addFriendship(2, 6); // Kevin Bacon (6) connected to 2

    addFriendship(3, 7);
    addFriendship(4, 8);
    addFriendship(5, 9);
    addFriendship(6, 10);
    addFriendship(6, 11);
    addFriendship(7, 12);
    addFriendship(8, 13);
    addFriendship(9, 14);
    addFriendship(10, 15);
    addFriendship(11, 16);
    addFriendship(12, 17);
    addFriendship(13, 18);
    addFriendship(14, 19);

    G social(people, edges);

    int you = 0;
    int kevin = 6;
    std::vector<int> path;

    bool connected = findPathBFS<int>(social, you, kevin, path);
    if (connected) {
        std::cout << "You are connected to Kevin Bacon.\n";
        std::cout << "Path (nodes): ";
        for (size_t i = 0; i < path.size(); ++i) {
            if (i) std::cout << " -> ";
            std::cout << path[i];
        }
        // Kevin Bacon number: number of edges in the path
        std::cout << "\nKevin Bacon number = " << (path.size() > 0 ? path.size() - 1 : 0) << "\n";
    }
    else {
        std::cout << "You are NOT connected to Kevin Bacon.\n";
    }

    // sanity test: try an isolated person (none of the above connects directly to someone new)
    // We'll make node 19 reachable, but if we remove its friendships it would be isolated.
    std::vector<int> unreachablePath;
    bool connectedTo19 = findPathBFS<int>(social, you, 19, unreachablePath);
    std::cout << "Connected to person 19? " << (connectedTo19 ? "yes" : "no") << "\n";

    return 0;
}
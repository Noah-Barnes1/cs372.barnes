#pragma once
#include "Graph.hpp"
#include <vector>
#include <set>

inline bool isSimpleCycle(Graph<int>& g, const std::vector<int>& path) {
    if (path.size() < 4) return false;
    if (path.front() != path.back()) return false;

    std::set<int> seen;
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        int a = path[i];
        int b = path[i + 1];
        if (!g.adjacent(a, b)) return false;
        if (i < path.size() - 1) {
            if (seen.find(a) != seen.end()) return false;
            seen.insert(a);
        }
    }

    if (seen.size() < 3) return false;

    return true;
}
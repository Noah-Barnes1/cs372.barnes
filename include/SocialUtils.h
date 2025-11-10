#pragma once
#include "Graph.hpp"
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

template <class N>
bool findPathBFS(Graph<N>& g, const N& start, const N& goal, std::vector<N>& outPath) {
    outPath.clear();
    if (start == goal) {
        outPath.push_back(start);
        return true;
    }

    std::queue<N> q;
    std::map<N, bool> visited;
    std::map<N, N> predecessor;

    q.push(start);
    visited[start] = true;

    bool found = false;
    while (!q.empty() && !found) {
        N current = q.front();
        q.pop();
        std::vector<N> neigh = g.neighbors(current);
        for (const N& n : neigh) {
            if (!visited[n]) {
                visited[n] = true;
                predecessor[n] = current;
                if (n == goal) {
                    std::vector<N> rev;
                    N cur = goal;
                    while (true) {
                        rev.push_back(cur);
                        if (cur == start) break;
                        cur = predecessor[cur];
                    }
                    std::reverse(rev.begin(), rev.end());
                    outPath = rev;
                    found = true;
                    break;
                }
                q.push(n);
            }
        }
    }

    if (!found) {
        outPath.clear();
        return false;
    }
    return true;
}
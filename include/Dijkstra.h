#pragma once
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <stdexcept>
#include <cassert>

inline std::vector<double> dijkstra(
    const std::vector<std::vector<std::pair<int, double>>>& graph,
    int source,
    std::vector<int>* outPrev = nullptr)
{
    const size_t n = graph.size();
    if (source < 0 || static_cast<size_t>(source) >= n) {
        throw std::out_of_range("dijkstra: source is out of graph range");
    }

    using Pair = std::pair<double, int>;
    const double INF = std::numeric_limits<double>::infinity();

    std::vector<double> dist(n, INF);
    std::vector<int> prev;
    if (outPrev) {
        prev.assign(n, -1);
        *outPrev = prev;
    }

    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    dist[source] = 0.0;
    pq.push({ 0.0, source });

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            double w = edge.second;
            assert(w > 0.0 && "Edge weights must be > 0 for Dijkstra");
            double alt = d + w;
            if (alt < dist[v]) {
                dist[v] = alt;
                if (outPrev) {
                    (*outPrev)[v] = u;
                }
                pq.push({ alt, v });
            }
        }
    }

    return dist;
}
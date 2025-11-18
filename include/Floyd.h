#pragma once
#include <vector>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <cstddef>

inline std::vector<std::vector<double>> floydWarshall(const std::vector<std::vector<double>>& W)
{
    const std::size_t n = W.size();
    if (n == 0) return std::vector<std::vector<double>>(); 
    for (const auto& row : W) {
        if (row.size() != n) {
            throw std::invalid_argument("floydWarshall: adjacency matrix must be square");
        }
    }

    const double INF = std::numeric_limits<double>::infinity();
    std::vector<std::vector<double>> D = W;
    for (std::size_t i = 0; i < n; ++i) {
        D[i][i] = 0.0;
    }
    for (std::size_t k = 0; k < n; ++k) {
        for (std::size_t i = 0; i < n; ++i) {
            if (D[i][k] == INF) continue;
            for (std::size_t j = 0; j < n; ++j) {
                if (D[k][j] == INF) continue;
                double alt = D[i][k] + D[k][j];
                if (alt < D[i][j]) {
                    D[i][j] = alt;
                }
            }
        }
    }

    return D;
}
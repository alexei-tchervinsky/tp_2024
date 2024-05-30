#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>

namespace lelkov
{
    void dijkstra(const std::vector<std::vector<int>> &graph, int start, int n);
    int getTreeDiameter(const std::vector<std::vector<int>> &graph, int n);
    void waveAlgorithm(const std::vector<std::vector<int>> &graph, int n, int start, int end);
}

#endif

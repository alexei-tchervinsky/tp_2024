#include "algorithms.hpp"
#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <utility>

namespace lelkov {
    const int INF = std::numeric_limits<int>::max();

    void dijkstra(const std::vector<std::vector<int>>& graph, int start, int n) {
        std::vector<int> dist(n, std::numeric_limits<int>::max());
        std::vector<int> parent(n, -1);
        std::vector<bool> visited(n, false);

        dist[start - 1] = 0;
        for (int i = 0; i < n - 1; i++) {
            int minDist = INF, u = -1;

            for (int j = 0; j < n; j++) {
                if (!visited[j] && dist[j] <= minDist) {
                    minDist = dist[j];
                    u = j;
                }
            }

            if (u == -1) {
                break;
            }

            visited[u] = true;

            for (int v = 0; v < n; v++) {
                if (graph[u][v] != INF && !visited[v] && dist[u] != INF) {
                    int newDist = dist[u] + graph[u][v];

                    if (newDist < dist[v]) {
                        dist[v] = newDist;
                        parent[v] = u;
                    }
                }
            }
        }

        std::cout << "Кратчайший путь от вершины " << start << ":\n";
        for (int i = 0; i < n; i++) {
            if (i == start - 1) {
                std::cout << i + 1 << ": нет пути от вершины " << start << " до вершины " << i + 1 << "\n";
            }
            else if (dist[i] == INF) {
                std::cout << i + 1 << ": нет пути от вершины " << start << " до вершины " << i + 1 << "\n";
            }
            else {
                std::cout << i + 1 << ": " << dist[i] << "\n";
            }
        }
    }

    int getTreeDiameter(const std::vector<std::vector<int>>& graph, int n) {
        int maxDiameter = 0;

        for (int i = 0; i < n; ++i) {
            std::vector<int> dist(n, INF);
            std::vector<int> parent(n, -1);
            std::vector<bool> visited(n, false);

            dist[i] = 0;

            for (int j = 0; j < n - 1; ++j) {
                int minDist = INF, u = -1;

                for (int k = 0; k < n; ++k) {
                    if (!visited[k] && dist[k] <= minDist) {
                        minDist = dist[k];
                        u = k;
                    }
                }

                if (u == -1) {
                    break;
                }

                visited[u] = true;

                for (int v = 0; v < n; ++v) {
                    if (graph[u][v] != INF && !visited[v] && dist[u] != INF) {
                        int newDist = dist[u] + graph[u][v];

                        if (newDist < dist[v]) {
                            dist[v] = newDist;
                            parent[v] = u;
                        }
                    }
                }
            }

            int longestPath = 0;
            for (int j = 0; j < n; ++j) {
                if (dist[j] > longestPath) {
                    longestPath = dist[j];
                }
            }

            if (longestPath > maxDiameter) {
                maxDiameter = longestPath;
            }
        }

        return maxDiameter;
    }

    void waveAlgorithm(const std::vector<std::vector<int>>& graph, int n, int start, int end) {
        start--;
        end--;

        std::vector<int> dist(n, INF);
        std::vector<bool> visited(n, false);
        std::vector<int> prev(n, -1);

        dist[start] = 0;
        std::queue<std::pair<int, int>> q;
        q.push({ start, 0 });
        visited[start] = true;

        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            int v = node.first;

            if (v == end) {
                break;
            }

            for (int u = 0; u < n; u++) {
                if (graph[v][u] != INF && !visited[u]) {
                    visited[u] = true;
                    dist[u] = dist[v] + graph[v][u];
                    prev[u] = v;
                    q.push({ u, node.second + 1 });
                }
            }
        }

        if (dist[end] == INF) {
            std::cout << "Путь не найден\n";
            return;
        }

        std::vector<int> path;
        int at = end;
        while (at != -1) {
            path.push_back(at);
            at = prev[at];
        }

        std::cout << "Кратчайший путь: ";
        for (int i = path.size() - 1; i >= 0; i--) {
            std::cout << path[i] + 1 << " ";
        }
        std::cout << "\nДлина пути: " << dist[end] << std::endl;
    }
}


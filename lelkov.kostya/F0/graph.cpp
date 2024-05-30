#include "algorithms.hpp"
#include "graph.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <vector>
#include <queue>

namespace lelkov {

    const int INF = std::numeric_limits<int>::max();

    Graph::Graph(int n) : n(n) {
        graph.resize(n, std::vector<int>(n, INF));
    }

    void Graph::inputGraph() {
        for (int i = 0; i < n; ++i) {
            std::cout << "Ребра из вершины " << i + 1 << ": ";
            for (int j = 0; j < n; ++j) {
                std::string s;
                while (true) {
                    try {
                        std::cin >> s;
                        if (s == "e") {
                            graph[i][j] = INF;
                        }
                        else {
                            int weight = std::stoi(s);
                            if (i == j || weight == 0) {
                                graph[i][j] = INF;
                            }
                            else {
                                graph[i][j] = weight;
                            }
                        }
                        break;
                    }
                    catch (const std::exception& e) {
                        std::cout << "Некорректный ввод. Вес ребра должен быть положительным числом больше нуля или 'e', если ребра нет.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (graph[i][j] != graph[j][i]) {
                    clearGraph();
                    throw std::runtime_error("Граф не является симметричным. Граф удален.");
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (graph[i][j] != INF) {
                    graph[j][i] = graph[i][j];
                }
            }
        }
        std::cout << "Граф создан.\n";
    }

    void Graph::clearGraph() {
        graph.clear();
    }

    void Graph::addNode() {
        int newSize = n + 1;
        graph.resize(newSize, std::vector<int>(newSize, INF));
        n = newSize;
        std::cout << "Вершина добавлена.\n";
    }

    void Graph::removeNode() {
        std::cout << "Введите номер вершины, которую хотите удалить или -1 чтобы выбрать другой алгоритм: ";
        int node;
        std::cin >> node;
        if (node == -1) {
            return;
        }
        if (node <= 0 || node > n || !std::cin) {
            throw std::runtime_error("Некорректный ввод!");
        }
        node--;
        graph.erase(graph.begin() + node);
        for (auto& row : graph) {
            row.erase(row.begin() + node);
        }
        n--;
        std::cout << "Вершина удалена.\n";
    }

    void Graph::addEdge() {
        int start, end, weight;
        std::cout << "Введите из какой вершины провести ребро, или -1 чтобы выбрать другой алгоритм: ";
        std::cin >> start;
        if (start == -1) {
            return;
        }
        if (start <= 0 || start > n || !std::cin) {
            throw std::runtime_error("Некорректный ввод! Вершина должна быть в диапазоне от 1 до " + std::to_string(n));
        }
        std::cout << "Введите в какую вершину провести ребро: ";
        std::cin >> end;
        if (end <= 0 || end > n || !std::cin) {
            throw std::runtime_error("Некорректный ввод! Вершина должна быть в диапазоне от 1 до " + std::to_string(n));
        }
        std::cout << "Введите вес ребра: ";
        std::cin >> weight;
        if (!std::cin) {
            throw std::runtime_error("Некорректный ввод! Вес ребра должен быть целым числом.");
        }

        if (start == end) {
            weight = 0;
        }

        graph[start - 1][end - 1] = weight;
        graph[end - 1][start - 1] = weight;
        std::cout << "Ребро создано.\n";
    }

    void Graph::removeEdge() {
        int start, end;
        std::cout << "Введите вершину, из которой хотите удалить ребро, или -1 чтобы выбрать другой алгоритм: ";
        std::cin >> start;
        if (start == -1) {
            return;
        }
        if (start <= 0 || start > n || !std::cin) {
            throw std::runtime_error("Некорректный ввод! Вершина должна быть в диапазоне от 1 до " + std::to_string(n));
        }
        std::cout << "Введите вершину, в которую хотите удалить ребро: ";
        std::cin >> end;
        if (end <= 0 || end > n || !std::cin) {
            throw std::runtime_error("Некорректный ввод! Вершина должна быть в диапазоне от 1 до " + std::to_string(n));
        }

        if (graph[start - 1][end - 1] == INF) {
            throw std::runtime_error("Некорректный ввод! Ребро между данными вершинами не существует.");
        }

        graph[start - 1][end - 1] = INF;
        graph[end - 1][start - 1] = INF;
        std::cout << "Ребро удалено.\n";
    }

    void Graph::findEdges() {
        int weight;
        std::cout << "Введите вес искомого ребра, или -1 чтобы выбрать другой алгоритм: ";
        std::cin >> weight;
        if (weight == -1) {
            return;
        }
        if (weight <= 0) {
            throw std::runtime_error("Некорректный ввод! Ребро должно иметь вес больше 0");
        }

        bool hasEdges = false;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (graph[i][j] == weight) {
                    hasEdges = true;
                    std::cout << "Ребро весом " << weight << " есть между вершинами " << i + 1 << " и " << j + 1 << std::endl;
                }
            }
        }

        if (!hasEdges) {
            std::cout << "Ребра весом " << weight << " не существует" << std::endl;
        }
    }

    void Graph::printGraph() {
        std::cout << "Матрица смежности графа:\n";

        std::cout << "    ";
        for (int i = 0; i < n; ++i) {
            std::cout << std::setw(5) << i + 1;
        }
        std::cout << "\n";

        std::cout << "    ";
        for (int i = 0; i < n; ++i) {
            std::cout << "-----";
        }
        std::cout << "\n";

        for (int i = 0; i < n; ++i) {
            std::cout << std::setw(2) << i + 1 << " |";
            for (int j = 0; j < n; ++j) {
                    if (graph[i][j] == INF) {
                    std::cout << std::setw(5) << "0";
                }
                else {
                    std::cout << std::setw(5) << graph[i][j];
                }
            }
            std::cout << "\n";
        }
    }

    bool Graph::isLinked() {
        int start, end;
        std::cout << "Введите одну вершину ребра: ";
        std::cin >> start;
        std::cout << "Введите вторую вершину ребра: ";
        std::cin >> end;

        if (start <= 0 || start > n || end <= 0 || end > n) {
            throw std::runtime_error("Некорректные вершины.");
        }

        if (graph[start - 1][end - 1] != INF) {
            std::cout << "Вершины " << start << " и " << end << " связаны.\n";
            return true;
        }
        else {
            std::cout << "Вершины " << start << " и " << end << " не связаны.\n";
            return false;
        }
    }

    bool Graph::hasNegativeEdges() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][j] < 0) {
                    return true;
                }
            }
        }
        return false;
    }

    int Graph::getNodeCount() const {
        return n;
    }

    void Graph::runDijkstra(int start) {
        dijkstra(graph, start, n);
    }

    int Graph::runGetTreeDiameter() {
        return getTreeDiameter(graph, n);
    }

    void Graph::runWaveAlgorithm(int start, int end) {
        waveAlgorithm(graph, n, start, end);
    }

    void printMenu() {
    std::cout << "---------------------------------\n";
    std::cout << "Меню:\n";
    std::cout << "1.  Ввести граф\n";
    std::cout << "2.  Вывести граф\n";
    std::cout << "3.  Добавить вершину\n";
    std::cout << "4.  Удалить вершину\n";
    std::cout << "5.  Добавить ребро\n";
    std::cout << "6.  Удалить ребро\n";
    std::cout << "7.  Проверить наличие ребра\n";
    std::cout << "8.  Поиск ребра по весу\n";
    std::cout << "9.  Определить диаметр дерева\n";
    std::cout << "10. Запустить алгоритм Дейкстры\n";
    std::cout << "11. Запустить волновой алгоритм\n";
    std::cout << "\n";
    std::cout << "Выберите действие: ";
}
}

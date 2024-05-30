#include "graph.hpp"
#include <iostream>
#include <limits>
#include <queue>
#include <memory>
#include <map>
#include <functional>

const int INF = std::numeric_limits<int>::max();

int main() {
    setlocale(LC_ALL, "Ru");
    std::unique_ptr<lelkov::Graph> graph = nullptr;
    bool running = true;

    std::map<int, std::function<void()>> commands = {
        {1, [&graph]() {
            int n;
            while (true) {
                std::cout << "Введите количество вершин графа: ";
                std::cin >> n;
                if (n < 0 || !std::cin) {
                    std::cout << "Количество вершин должно быть положительным числом!\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                    break;
                }
            }
            graph = std::make_unique<lelkov::Graph>(n);
            graph->inputGraph();
        }},
        {2, [&graph]() {
            if (graph == nullptr) {
                std::cout << "Сначала введите граф (опция 1).\n";
            } else {
                graph->printGraph();
            }
        }},
        {3, [&graph]() {
            if (graph == nullptr) {
                std::cout << "Сначала введите граф (опция 1).\n";
            } else {
                graph->addNode();
            }
        }},
        {4, [&graph]() {
            if (graph == nullptr) {
                std::cout << "Сначала введите граф (опция 1).\n";
            } else {
                graph->removeNode();
            }
        }},
        {5, [&graph]() {
            if (graph == nullptr) {
                std::cout << "Сначала введите граф (опция 1).\n";
            } else {
                graph->addEdge();
            }
        }},
        {6, [&graph]() {
            if (graph == nullptr) {
                std::cout << "Сначала введите граф (опция 1).\n";
            } else {
                graph->removeEdge();
            }
        }},
        {7, [&graph]() {
            if (graph == nullptr) {
                std::cout << "Сначала введите граф (опция 1).\n";
            } else {
                graph->isLinked();
            }
        }},
        {8, [&graph]() {
            if (graph == nullptr) {
                std::cout << "Сначала введите граф (опция 1).\n";
            } else {
                graph->findEdges();
            }
        }},
        {9, [&graph]() {
            if (graph == nullptr) {
                std::cout << "Сначала введите граф (опция 1).\n";
            } else {
                try {
                    int diameter = graph->runGetTreeDiameter();
                    std::cout << "Диаметр дерева: " << diameter << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                }
            }
        }},
        {10, [&graph]() {
            if (graph == nullptr) {
                std::cout << "Сначала введите граф (опция 1).\n";
            } else {
                int start;
                std::cout << "Введите начальную вершину поиска: ";
                std::cin >> start;
                if (start <= 0 || start > graph->getNodeCount() || !std::cin) {
                    std::cout << "Некорректный ввод!\n";
                } else {
                    graph->runDijkstra(start);
                }
            }
        }},
        {11, [&graph]() {
            if (graph == nullptr) {
                std::cout << "Сначала введите граф (опция 1).\n";
            } else {
                int start, end;
                std::cout << "Введите начальную вершину поиска: ";
                std::cin >> start;
                std::cout << "Введите конечную вершину поиска: ";
                std::cin >> end;
                if (start <= 0 || start > graph->getNodeCount() || end <= 0 || end > graph->getNodeCount() || !std::cin) {
                    std::cout << "Некорректный ввод!\n";
                } else {
                    graph->runWaveAlgorithm(start, end);
                }
            }
        }}
    };

    while (running) {
        lelkov::printMenu();
        int choice;
        std::cin >> choice;
        if (std::cin.eof()){
            running = false;
            break;
        }
        std::cout << "---------------------------------\n";

        try {
            if (commands.find(choice) != commands.end()) {
                commands[choice]();
            } else {
                std::cout << "Некорректный выбор. Попробуйте снова.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}

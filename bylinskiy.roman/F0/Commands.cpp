#include <iostream>
#include <fstream>
#include <limits>
#include <queue>
#include <functional>
#include <algorithm>
#include "Commands.h"
#include "GraphUtils.h"

void resetDijkstra(Graph& graph) {
    graph.distances.clear();
    graph.predecessors.clear();
    for (const auto& pair : graph.adjList) {
        graph.distances[pair.first] = std::numeric_limits< int >::max();
    }
}

void dijkstraCommand(std::istream& input, std::ostream& output, Graph& graph) {
    std::string startVertex;
    input >> startVertex;

    iofmtguard guard(output);

    if (graph.adjList.find(startVertex) == graph.adjList.end()) {
        output << "Vertex does not exist\n";
    }
    else {
        resetDijkstra(graph);

        graph.distances[startVertex] = 0;
        using QueueElement = std::pair< int, std::string >;
        std::priority_queue< std::pair< int, std::string >, std::vector< std::pair< int, std::string > >, std::greater<> > priorityQueue;
        priorityQueue.emplace(0, startVertex);

        while (!priorityQueue.empty()) {
            QueueElement current = priorityQueue.top();
            int currentDistance = current.first;
            std::string currentVertex = current.second;
            priorityQueue.pop();

            if (currentDistance > graph.distances[currentVertex]) {
                continue;
            }
            for (const auto& neighborWeightPair : graph.adjList[currentVertex]) {
                const std::string& neighbor = neighborWeightPair.first;
                int weight = neighborWeightPair.second;

                int distance = currentDistance + weight;
                if (distance < graph.distances[neighbor]) {
                    graph.distances[neighbor] = distance;
                    graph.predecessors[neighbor] = currentVertex;
                    priorityQueue.emplace(distance, neighbor);
                }
            }
        }
    }
}

void shortestPathCommand(std::istream& input, std::ostream& output, const Graph& graph) {
    std::string startVertex, endVertex;
    input >> startVertex >> endVertex;

    iofmtguard guard(output);

    if (graph.distances.find(endVertex) == graph.distances.end()) {
        output << "One of the vertices doesn't exists\n";
    }
    else if (graph.distances.at(endVertex) == std::numeric_limits< int >::max()) {
        output << "No path between vertices\n";
    }
    else {
        std::vector< std::string > path;
        std::string current = endVertex;

        while (current != startVertex) {
            path.push_back(current);
            current = graph.predecessors.at(current);
        }
        path.push_back(startVertex);
        std::reverse(path.begin(), path.end());

        for (const auto& vertex : path) {
            output << vertex << " ";
        }
        output << "\n";
    }
}

void addCommand(std::istream& input, std::ostream& output, Graph& graph) {
    std::string type;
    input >> type;

    iofmtguard guard(output);

    if (type == "v") {
        std::string vertex;
        input >> vertex;
        addVertex(graph, vertex);
    }
    else if (type == "e") {
        std::string vertex1, vertex2;
        int weight;
        input >> vertex1 >> vertex2 >> weight;
        addEdge(graph, vertex1, vertex2, weight);
    }
    else {
        printInvalidCommand(output);
    }
}

void delCommand(std::istream& input, std::ostream& output, Graph& graph) {
    std::string type;
    input >> type;

    iofmtguard guard(output);

    if (type == "v") {
        std::string vertex;
        input >> vertex;
        deleteVertex(graph, vertex);
    }
    else if (type == "e") {
        std::string vertex1, vertex2;
        input >> vertex1 >> vertex2;
        deleteEdge(graph, vertex1, vertex2);
    }
    else {
        printInvalidCommand(output);
    }
}

void showGraphCommand(std::ostream& output, const Graph& graph) {
    for (const auto& vertexEdgesPair : graph.adjList) {
        const auto& vertex = vertexEdgesPair.first;
        const auto& edges = vertexEdgesPair.second;
        output << vertex << ": ";
        for (const auto& neighborWeightPair : edges) {
            const auto& neighbor = neighborWeightPair.first;
            const auto& weight = neighborWeightPair.second;
            output << "(" << neighbor << ", " << weight << ") ";
        }
        output << "\n";
    }
}

void updateEdgeCommand(std::istream& input, std::ostream& output, Graph& graph) {
    std::string type;
    input >> type;

    iofmtguard guard(output);

    if (type == "e") {
        std::string vertex1, vertex2;
        int newWeight;
        input >> vertex1 >> vertex2 >> newWeight;
        updateEdge(graph, vertex1, vertex2, newWeight);
    }
    else {
        printInvalidCommand(output);
    }
}

void printInvalidCommand(std::ostream& output) {
    iofmtguard guard(output);

    output << "<INVALID COMMAND>\n";
}

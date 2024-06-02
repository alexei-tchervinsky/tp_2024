#include "Graph.hpp"
#include <iostream>
#include <queue>

namespace graph {
// Initialize an empty graph
void Graph::initialize() {
  for (int i = 0; i < MAX_NODES; ++i) {
    nodes[i] = false;
    for (int j = 0; j < MAX_NODES; ++j) {
      adjMatrix[i][j] = false;
    }
  }
  numOfNodes = 0;
}

// Check if the graph has any nodes
bool Graph::hasNodes() const {
  for (int i = 0; i < MAX_NODES; ++i) {
    if (nodes[i]) {
      return true;
    }
  }
  return false;
}

// Check if a specific node exists in the graph
bool Graph::hasNode(int node) const {
  if (node < 0 || node >= MAX_NODES) {
    return false;
  }
  return nodes[node];
}

// Check if there is an edge between two given nodes
bool Graph::hasEdge(int node1, int node2) const {
  if (!hasNode(node1) || !hasNode(node2)) {
    return false;
  }
  return adjMatrix[node1][node2];
}

// Add a new node to the graph
void Graph::addNode(int node) {
  if (node < 0 || node >= MAX_NODES) {
    return;
  }
  nodes[node] = true;
  numOfNodes++;
}

// Add a new edge to the graph
void Graph::addEdge(int node1, int node2) {
  if (!hasNode(node1) || !hasNode(node2)) {
    throw "One or both nodes do not exist.";
  }
  adjMatrix[node1][node2] = true;
  adjMatrix[node2][node1] = true;
}

std::size_t Graph::getNumOfNodes() { return numOfNodes; }
// Remove a node from the graph
void Graph::removeNode(int node) {
  if (!hasNode(node))
    return;
  for (int i = 0; i < MAX_NODES; ++i) {
    adjMatrix[node][i] = false;
    adjMatrix[i][node] = false;
  }
  nodes[node] = false;
}

// Breadth-First Search (BFS)
void Graph::bfs(int start) const {
  if (!hasNode(start)) {
    throw "Start node does not exist.";
  }

  bool visited[MAX_NODES] = {false};
  std::queue<int> queue;
  queue.push(start);
  visited[start] = true;

  while (!queue.empty()) {
    int current = queue.front();
    queue.pop();
    std::cout << current << " ";

    for (int i = 0; i < MAX_NODES; ++i) {
      if (adjMatrix[current][i] && !visited[i]) {
        queue.push(i);
        visited[i] = true;
      }
    }
  }
  std::cout << std::endl;
}

// Shortest paths algorithm (BFS for unweighted graph)
void Graph::shortestPaths(int start) const {
  if (!hasNode(start)) {
    throw "Start node does not exist.";
  }

  int distances[MAX_NODES];
  for (int i = 0; i < MAX_NODES; ++i) {
    distances[i] = -1;
  }
  distances[start] = 0;

  std::queue<int> queue;
  queue.push(start);

  while (!queue.empty()) {
    int current = queue.front();

    for (int i = 0; i < MAX_NODES; ++i) {
      if (adjMatrix[current][i] && distances[i] == -1) {
        distances[i] = distances[current] + 1;
        queue.push(i);
      }
    }
  }

  std::cout << "Кратчайшие пути от узла " << start << ":" << std::endl;
  for (int i = 0; i < MAX_NODES; ++i) {
    if (distances[i] != -1) {
      std::cout << "Узел " << i << ", Расстояние: " << distances[i]
                << std::endl;
    }
  }
}

// Calculate the diameter of the graph
int Graph::calculateDiameter() const {
  if (!hasNodes())
    return 0;

  int diameter = 0;
  for (int i = 0; i < MAX_NODES; ++i) {
    if (nodes[i]) {
      int distances[MAX_NODES];
      for (int j = 0; j < MAX_NODES; ++j) {
        distances[j] = -1;
      }
      distances[i] = 0;

      std::queue<int> queue;
      queue.push(i);

      while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int k = 0; k < MAX_NODES; ++k) {
          if (adjMatrix[current][k] && distances[k] == -1) {
            distances[k] = distances[current] + 1;
            queue.push(k);
            diameter = std::max(diameter, distances[k]);
          }
        }
      }
    }
  }
  return diameter;
}

// Print the graph for debugging
void Graph::printGraph() const {
  for (int i = 0; i < MAX_NODES; ++i) {
    if (nodes[i]) {
      std::cout << i << ": ";
      for (int j = 0; j < MAX_NODES; ++j) {
        if (adjMatrix[i][j]) {
          std::cout << j << " ";
        }
      }
      std::cout << std::endl;
    }
  }
}
} // namespace graph

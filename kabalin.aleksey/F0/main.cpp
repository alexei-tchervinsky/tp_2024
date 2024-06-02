#include "Graph.hpp"
#include <iostream>
using namespace graph;
void displayMenu() {
  std::cout << "Graph Menu:\n";
  std::cout << "1. Create a graph\n";
  std::cout << "2. Add an edge\n";
  std::cout << "3. Print the graph\n";
  std::cout << "4. Remove a node\n";
  std::cout << "5. Check is node in graph\n";
  std::cout << "6. Check is nodes connected\n";
  std::cout << "7. Add node to graph\n";
  std::cout << "8. BFS\n";
  std::cout << "9. Shortest path\n";
  std::cout << "10. Calculate diametr of the graph\n";
  std::cout << "11. Exit\n";
  std::cout << "Enter your choice: ";
}

int main() {
  Graph *graph = nullptr;
  int choice, vertices, src, dest;

  while (true) {
    displayMenu();
    std::cin >> choice;
    if (std::cin.eof()) {
      return 0;
    }

    switch (choice) {
    case 1:
      std::cout << "Enter the number of vertices: ";
      std::cin >> vertices;
      graph = new Graph();
      for (int i = 1; i < vertices + 1; i++) {
        graph->addNode(i);
      }
      std::cout << "Graph created with " << vertices << " vertices.\n";
      break;

    case 2:
      if (graph == nullptr) {
        std::cout << "Please create a graph first.\n";
        break;
      }
      std::cout << "Enter source vertex: ";
      std::cin >> src;
      std::cout << "Enter destination vertex: ";
      std::cin >> dest;
      if (!graph->hasNode(src) || !graph->hasNode(dest)) {
        std::cout << "Invalid vertices. Please try again.\n";
        break;
      }
      graph->addEdge(src, dest);
      std::cout << "Edge added between " << src << " and " << dest << ".\n";
      break;

    case 3:
      if (graph == nullptr) {
        std::cout << "Please create a graph first.\n";
        break;
      }
      graph->printGraph();
      break;

    case 4:
      if (graph == nullptr) {
        std::cout << "Please create a graph first.\n";
        break;
      }
      std::cout << "Enter vertex to remove: ";
      std::cin >> src;
      if (!graph->hasNode(src)) {
        std::cout << "Invalid vertex. Please try again.\n";
        break;
      }
      graph->removeNode(src);
      std::cout << "Vertex " << src << " removed.\n";
      break;

    case 5:
      if (graph == nullptr) {
        std::cout << "Please create a graph first.\n";
        break;
      }
      std::cout << "Enter the vertex: ";
      std::cin >> src;
      if (graph->hasNode(src)) {
        std::cout << "Vertex " << src << " is in the graph.\n";
      } else {
        std::cout << "Vertex " << src << " is not in the graph.\n";
      }
      break;

    case 6:
      if (graph == nullptr) {
        std::cout << "Please create a graph first.\n";
        break;
      }
      std::cout << "Enter source vertex: ";
      std::cin >> src;
      std::cout << "Enter destination vertex: ";
      std::cin >> dest;
      if (!graph->hasNode(src) || !graph->hasNode(dest)) {
        std::cout << "Invalid vertices. Please try again.\n";
        break;
      }
      if (graph->hasEdge(src, dest)) {
        std::cout << "Vertices " << src << " and " << dest
                  << " are connected.\n";
      } else {
        std::cout << "Vertices " << src << " and " << dest
                  << " are not connected.\n";
      }
      break;

    case 7:
      if (graph == nullptr) {
        std::cout << "Please create a graph first.\n";
        break;
      }
      std::cout << "Enter node to bfs: ";
      std::cin >> src;
      graph->bfs(src);

      graph->addNode(graph->getNumOfNodes() + 1);
      std::cout << "Node are added\nNow graph has " << graph->getNumOfNodes()
                << " nodes\n";
      break;
    case 9:
      if (graph == nullptr) {
        std::cout << "Please create a graph first.\n";
        break;
      }
      std::cout << "Enter node to shortest path: ";
      std::cin >> src;
      graph->shortestPaths(src);
      break;
    case 10:
      if (graph == nullptr) {
        std::cout << "Please create a graph first.\n";
        break;
      }
      std::cout << "Diametr of the graph is " << graph->calculateDiameter()
                << '\n';
      break;
    case 11:
      std::cout << "Thank you!\n";
      return 0;
    default:
      std::cout << "Invalid choice. Please try again.\n";
      break;
    }
  }
}

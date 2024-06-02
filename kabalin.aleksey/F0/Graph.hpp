#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cstddef>
const int MAX_NODES = 100; // Maximum number of nodes in the graph
namespace graph {
class Graph {
public:
  Graph() { initialize(); }
  void initialize();
  bool hasNodes() const;
  bool hasNode(int node) const;
  bool hasEdge(int node1, int node2) const;
  void addNode(int node);
  void addEdge(int node1, int node2);
  void removeNode(int node);
  void bfs(int start) const;
  void shortestPaths(int start) const;
  int calculateDiameter() const;
  void printGraph() const;
  std::size_t getNumOfNodes();

private:
  bool nodes[MAX_NODES];
  bool adjMatrix[MAX_NODES][MAX_NODES];
  std::size_t numOfNodes;
};

} // namespace graph

#endif

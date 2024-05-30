#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <string>

struct Graph {
  std::map< std::string, std::map< std::string, int > > adjList;
  std::map< std::string, int > distances;
  std::map< std::string, std::string > predecessors;
};

#endif

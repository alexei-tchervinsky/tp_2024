#ifndef GRAPHUTILS_H
#define GRAPHUTILS_H

#include <iosfwd>
#include <map>
#include "Graph.h"

void addVertex(Graph& graph, const std::string& vertex);
void addEdge(Graph& graph, const std::string& vertex1, const std::string& vertex2, int weight);
void deleteVertex(Graph& graph, const std::string& vertex);
void deleteEdge(Graph& graph, const std::string& vertex1, const std::string& vertex2);
void updateEdge(Graph& graph, const std::string& vertex1, const std::string& vertex2, int newWeight);

#endif

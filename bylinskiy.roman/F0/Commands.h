#ifndef COMMANDS_H
#define COMMANDS_H

#include <iosfwd>
#include <string>
#include "Graph.h"

void printInvalidCommand(std::ostream& output);
void dijkstraCommand(std::istream& input, std::ostream& output, Graph& graph);
void shortestPathCommand(std::istream& input, std::ostream& output, const Graph& graph);
void addCommand(std::istream& input, std::ostream& output, Graph& graph);
void delCommand(std::istream& input, std::ostream& output, Graph& graph);
void showGraphCommand(std::ostream& output, const Graph& graph);
void updateEdgeCommand(std::istream& input, std::ostream& output, Graph& graph);

#endif

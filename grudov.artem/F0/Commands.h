#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <exception>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stack>
#include <limits>
#include <iostream>
#include <algorithm>

#include "Delimiter.h"

namespace grudov
{
    using Graph = std::vector<std::vector<bool>>;

    void help(std::ostream& out);
    void show(Graph& graph, std::ostream& out);
    void add_vertex(Graph& graph,  std::ostream& out);
    void delete_vertex(Graph& graph, std::istream& in, std::ostream& out);
    void add_edge(Graph& graph, std::istream& in, std::ostream& out);
    void empty(Graph& graph, std::ostream& out);
    void check_vertex(Graph& graph, std::istream& in, std::ostream& out);
    void check_edge(Graph& graph, std::istream& in, std::ostream& out);
    void check_any_edge(Graph& graph, std::ostream& out);
    void DFS(Graph& graph, std::istream& in, std::ostream& out);
    void Topological_sort(Graph& graph, std::ostream& out);

    void DFS_rec(Graph &graph,  std::ostream &out, std::vector<bool>& visited, std::size_t from);
    void Topological_sort_rec(Graph &graph, std::vector<int>& visited, std::stack<int>& order, std::size_t from);

}

#endif

#include "Commands.h"


void grudov::help(std::ostream& out)
{
    out << "Commands:\n" <<
    "HELP - output all commands\n" <<
    "DFS n - output Depth-First-Search for the graph (n - vertex where algorithm begins)\n" <<
    "TOP_SORT - output the topological sort for graph\n" <<
    "ADD_VERTEX - add vertex \n" <<
    "ADD_EDGE n1 n2 - add edge from n1 to n2 (n1, n2 - keys)\n" <<
    "DELETE_VERTEX n - delete vertex (n - key)\n" <<
    "CHECK_VERTEX n - check vertex int the graph(n - key)\n" <<
    "CHECK_EDGE n1 n2 - check edge from n1 to n2 (n1, n2 - keys)\n" <<
    "CHECK_ANY_EDGE - check any edge \n" <<
    "SHOW - show graph(adjency matrix)\n\n";
}

void grudov::show(Graph& graph, std::ostream& out)
{
    if(!graph.size()){
        out << "GRAPH IS EMPTY\n";
    } else {
        out << std::setw(10) << "|";
        for(std::size_t i = 0; i < graph.size(); i++) {
            out << std::setw(5) << i+1 << std::setw(5) << "|";
        }
        out << "\n";
        for(std::size_t i = 0; i < graph.size(); i++){
            for(std::size_t j = 0; j < graph[i].size()+1; j++){
                out << std::setw(10) << "__________";
            }
            out << "\n";
            out << std::setw(5) << i+1 << std::setw(5) << "|";
            for(std::size_t j = 0; j < graph[i].size(); j++){
                out << std::setw(5) << graph[i][j] << std::setw(5) << "|";
            }
            out << "\n";
        }
    }
}

void grudov::add_vertex(Graph& graph, std::ostream& out){
    if(!graph.size()) {
        std::vector<bool> temp(1);
        temp[0] = 0;
        graph.push_back(temp);
    } else {
        std::vector<bool> temp(graph[0].size());
        for(std::size_t i = 0; i < temp.size(); i++){
            temp[i] = 0;
        }
        graph.push_back(temp);
        for(std::size_t i = 0; i < graph.size(); i++){
            graph[i].push_back(0);
        }
    }
}
void grudov::delete_vertex(Graph &graph, std::istream &in, std::ostream &out)
{
    int vertex;
    in >> vertex;
    if (!in)
    {
        throw std::invalid_argument("<INVALID COMMAND>");
    }
    if(static_cast<std::size_t>(vertex) > graph.size() || vertex < 1){
        throw std::invalid_argument("<VERTEX DOESNT EXIST>");
    }
    vertex--;
    graph.erase(graph.begin()+vertex);
    for(std::size_t i = 0; i < graph.size(); i++){
        graph[i].erase(graph[i].begin()+vertex);
    }
}
void grudov::add_edge(Graph &graph, std::istream &in, std::ostream &out)
{
    int vertex1, vertex2;
    in >> vertex1;
    if (!in)
    {
        throw std::invalid_argument("<INVALID COMMAND>");
    }
    if(static_cast<std::size_t>(vertex1) > graph.size() || vertex1 < 1){
        throw std::invalid_argument("<VERTEX DOESNT EXIST>");
    }

    in >> vertex2;
    if (!in)
    {
        throw std::invalid_argument("<INVALID COMMAND>");
    }
    if(static_cast<std::size_t>(vertex2) > graph.size() || vertex2 < 1){
        throw std::invalid_argument("<VERTEX DOESNT EXIST>");
    }
    graph[vertex1-1][vertex2-1] = 1;
}

void grudov::empty(Graph &graph, std::ostream &out)
{
    if(!graph.size()) {
        out << "GRAPH IS EMPTY\n";
    } else {
        out << "GRAPH ISNT EMPTY\n";
    }
}

void grudov::check_vertex(Graph &graph, std::istream &in, std::ostream &out)
{
    int vertex;
    in >> vertex;
    if (!in)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    if(static_cast<std::size_t>(vertex) > graph.size() || vertex < 1){
        out << "VERTEX DOESN EXIST\n";
    }else {
        out << "VERTEX EXIST\n";
    }
}

void grudov::check_edge(Graph &graph, std::istream &in, std::ostream &out)
{
    int vertex1, vertex2;
    in >> vertex1;
    if (!in)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    if(static_cast<std::size_t>(vertex1) > graph.size() || vertex1 < 1){
        throw std::invalid_argument("<VERTEX DOESNT EXIST>");
    }

    in >> vertex2;
    if (!in)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    if(static_cast<std::size_t>(vertex2) > graph.size() || vertex2 < 1){
        throw std::invalid_argument("<VERTEX DOESNT EXIST>");
    }
    if(graph[vertex1-1][vertex2-1]){
        out << "EDGE FROM " << vertex1 << " TO " << vertex2 << " EXIST\n";
    }else {
        out << "EDGE FROM " << vertex1 << " TO " << vertex2 << "DOESN EXIST\n";
    }
}

void grudov::check_any_edge(Graph &graph,  std::ostream &out)
{
    for(std::size_t i = 0; i < graph.size(); i++){
        for(std::size_t j = 0; j < graph.size(); j++){
            if(graph[i][j]){
                out << "EDGES EXIST\n";
                return;
            }
        }
    }
    out << "EDGES DOESNT EXIST\n";
}

void grudov::DFS(Graph &graph, std::istream &in, std::ostream &out)
{
    if(!graph.size()){
        out << "GRAP IS EMPTY\n";
    } else {
        int vertex;
        in >> vertex;
        if (!in)
        {
          throw std::invalid_argument("<INVALID COMMAND>");
        }
        if(static_cast<std::size_t>(vertex) > graph.size() || vertex < 1){
            throw std::invalid_argument("<VERTEX DOESNT EXIST>");
        }
        std::vector<bool> visited(graph.size());
        out << "DEPTH-FIRST-SEARCH FROM VERTEX: "<< vertex <<"\n";
        DFS_rec(graph, out, visited, vertex-1);
        out <<"\n";
    }
}

void grudov::Topological_sort(Graph &graph, std::ostream &out)
{
    if(!graph.size()){
        out << "GRAP IS EMPTY\n";
    } else {
        std::stack<int> order;
        std::vector<int> visited(graph.size());
        for(std::size_t i = 0; i < graph.size(); i++){
           Topological_sort_rec(graph, visited, order, i);
        }
        out << "Topological sort: " << "\n";
        while(!order.empty()){
            out << order.top() << " ";
            order.pop();
        }
        out <<"\n";
    }
}

void grudov::DFS_rec(Graph &graph, std::ostream &out, std::vector<bool> &visited, std::size_t from)
{
    visited[from] = 1;
    out << from+1 << " ";
    for(std::size_t to = 0; to < graph[from].size(); to++){
        if(graph[from][to] && !visited[to]){
            DFS_rec(graph, out, visited, to);
        }
    }
}

void grudov::Topological_sort_rec(Graph &graph, std::vector<int> &visited, std::stack<int> &order, std::size_t from)
{
    if(visited[from] != 2){
        visited[from] = 1;
        for(std::size_t to = 0; to < graph[from].size(); to++){
            if(graph[from][to]){
                if(visited[to] == 0){
                    Topological_sort_rec(graph, visited, order, to);
                }
                if(visited[to] == 1){
                    throw std::invalid_argument("<GRAPH CYCLED>");
                }
            }
        }
        visited[from] = 2;
        order.push(from+1);
    }
}

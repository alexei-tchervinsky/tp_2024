#include "Commands.h"
#include <iostream>
#include <functional>
#include <map>

int main()
{
    using Graph = std::vector<std::vector<bool>>; //индексы - это числа, которые являются значениями
    Graph graph;

    std::map< std::string, std::function< void (Graph&, std::istream&, std::ostream&) > > command;
    {
        using namespace std::placeholders;
        command["HELP"] = std::bind(grudov::help, _3);
        command["ADD_VERTEX"] = std::bind(grudov::add_vertex, _1, _3);
        command["DELETE_VERTEX"] = std::bind(grudov::delete_vertex, _1, _2, _3);
        command["ADD_EDGE"] = std::bind(grudov::add_edge, _1, _2,_3);
        command["CHECK_ANY_EDGE"] = std::bind(grudov::check_any_edge, _1, _3);
        command["CHECK_EDGE"] = std::bind(grudov::check_edge, _1, _2, _3);
        command["CHECK_VERTEX"] = std::bind(grudov::check_vertex, _1, _2, _3);
        command["EMPTY"] = std::bind(grudov::empty, _1, _3);
        command["DFS"] = std::bind(grudov::DFS, _1, _2, _3);
        command["TOP_SORT"] = std::bind(grudov::Topological_sort, _1, _3);
        command["SHOW"] = std::bind(grudov::show, _1, _3);
    }
    std::cout << "Enter 'HELP' to get the list of all available commands.\n";

    std::string cmd = "";
    while (std::cin >> cmd){
        try{
            command.at(cmd)(graph, std::cin, std::cout);
        }catch (const std::exception& ex) {
            std::cerr << ex.what() << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
    }
}

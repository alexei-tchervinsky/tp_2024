#include <iostream>
#include <functional>
#include <limits>
#include <map>
#include "Graph.h"
#include "Commands.h"

int main() {
    Graph graph;
    std::map< std::string, std::function< void(std::istream&, std::ostream&, Graph&) > > cmds;

    cmds["add"] = std::bind(addCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cmds["del"] = std::bind(delCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cmds["dijkstra"] = std::bind(dijkstraCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cmds["path"] = std::bind(shortestPathCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cmds["show"] = std::bind(showGraphCommand, std::placeholders::_2, std::placeholders::_3);
    cmds["update"] = std::bind(updateEdgeCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    try {
        std::string cmd;
        while (std::cin >> cmd) {
            auto it = cmds.find(cmd);
            if (it != cmds.end()) {
                it->second(std::cin, std::cout, graph);
            }
            else {
                printInvalidCommand(std::cout);
                std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
            }
        }
    }
    catch (const std::logic_error& e) {
        std::cerr << "There was an error: " << e.what();
    }

    return 0;
}

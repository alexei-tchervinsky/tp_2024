#include "functions.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
using namespace geometry;

int main()
{

    std::vector<geometry::Shape> shapes;

    string command;
    while (getline(cin, command))
    {
        istringstream iss(command);
        string cmd, type;
        iss >> cmd >> type;

        if (cmd == "COUNT")
        {
            geometry::countCommand(shapes, type);
        }
        else if (cmd == "AREA")
        {
            geometry::areaCommand(shapes, type);
        }
        else if (cmd == "MAX")
        {
            geometry::maxCommand(shapes, type);
        }
        else if (cmd == "RECTS")
        {
            geometry::rectsCommand(shapes);
        }
        else
        {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}

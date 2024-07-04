#include "functions.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
using namespace geometry;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << "FILENAME_NOT_SPECIFIED\n";
        return 1;
    }

    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "FILE_NOT_FOUND\n";
        return 1;
    }

    vector<Polygon> polygons;
    read_polygons(in, polygons);

    string command;
    while (getline(cin, command))
    {
        istringstream iss(command);
        string cmd, type;
        iss >> cmd >> type;

        if (cmd == "AREA")
        {
            area_param(polygons, iss, cout);
        }
        else if (cmd == "MAX")
        {
            extreme_param(polygons, iss, cout, true, type);
        }
        else if (cmd == "MIN")
        {
            extreme_param(polygons, iss, cout, false, type);
        }
        else if (cmd == "COUNT")
        {
            count_param(polygons, iss, cout);
        }
        else if (cmd == "RECTS")
        {
            rects_param(polygons, iss, cout);
        }
        else if (cmd == "MAXSEQ")
        {
            maxseq_param(polygons, iss, cout);
        }
        else
        {
            cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}

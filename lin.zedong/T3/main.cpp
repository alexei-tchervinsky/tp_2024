#include "functions.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
using namespace geometry;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: ./program filename" << endl;
        return 1;
    }

    vector<Polygon> polygons;
    ifstream inputFile(argv[1]);
    if (!inputFile)
    {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    read_polygons(inputFile, polygons);

    string command;
    while (getline(cin, command))
    {
        istringstream iss(command);
        string cmd;
        iss >> cmd;

        if (cmd == "AREA")
        {
            area_param(polygons, iss, cout);
        }
        else if (cmd == "MAX")
        {
            max_param(polygons, iss, cout);
        }
        else if (cmd == "MIN")
        {
            min_param(polygons, iss, cout);
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
            cout << "<INVALID COMMAND>" << endl;
        }
    }

    return 0;
}

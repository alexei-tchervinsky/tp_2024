#include "functions.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: ./program filename" << endl;
        return 1;
    }

    vector<geometry::Polygon> polygons;
    ifstream inputFile(argv[1]);
    if (!inputFile)
    {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    geometry::read_polygons(inputFile, polygons);

    string command;
    while (getline(cin, command))
    {
        istringstream iss(command);
        string cmd;
        iss >> cmd;

        if (cmd == "AREA")
        {
            string param;
            iss >> param;
            if (param == "ODD" || param == "EVEN")
            {
                double result = geometry::get_area_sum(polygons, [&](const geometry::Polygon& poly)
                {
                    return (poly.points.size() % 2 == 0) == (param == "EVEN");
                });
                cout << fixed << setprecision(1) << result << endl;
            }
            else if (param == "MEAN")
            {
                if (polygons.size() > 0)
                {
                    double result = geometry::get_mean_area(polygons);
                    cout << fixed << setprecision(1) << result << endl;
                }
                else
                {
                    cout << "<INVALID COMMAND>" << endl;
                }
            }
            else
            {
                int num;
                istringstream(param) >> num;
                if (num > 0)
                {
                    double result = geometry::get_area_sum(polygons, [&](const geometry::Polygon& poly)
                    {
                        return poly.points.size() == static_cast<std::vector<geometry::Point>::size_type>(num);
                    });
                    cout << fixed << setprecision(1) << result << endl;
                }
                else
                {
                    cout << "<INVALID COMMAND>" << endl;
                }
            }
        }
        else if (cmd == "MAX")
        {
            string param;
            iss >> param;
            if (param == "AREA")
            {
                if (polygons.size() > 0)
                {
                    double result = geometry::get_max_area(polygons);
                    cout << fixed << setprecision(1) << result << endl;
                }
                else
                {
                    cout << "<INVALID COMMAND>" << endl;
                }
            }
            else if (param == "VERTEXES")
            {
                if (polygons.size() > 0)
                {
                    int result = geometry::get_max_vertexes(polygons);
                    cout << result << endl;
                }
                else
                {
                    cout << "<INVALID COMMAND>" << endl;
                }
            }
            else
            {
                cout << "<INVALID COMMAND>" << endl;
            }
        }
        else if (cmd == "MIN")
        {
            string param;
            iss >> param;
            if (param == "AREA")
            {
                if (polygons.size() > 0)
                {
                    double result = geometry::get_min_area(polygons);
                    cout << fixed << setprecision(1) << result << endl;
                }
                else
                {
                    cout << "<INVALID COMMAND>" << endl;
                }
            }
            else if (param == "VERTEXES")
            {
                if (polygons.size() > 0)
                {
                    int result = geometry::get_min_vertexes(polygons);
                    cout << result << endl;
                }
                else
                {
                    cout << "<INVALID COMMAND>" << endl;
                }
            }
            else
            {
                cout << "<INVALID COMMAND>" << endl;
            }
        }
        else if (cmd == "COUNT")
        {
            string param;
            iss >> param;
            if (param == "EVEN")
            {
                int result = geometry::count_even_vertexes(polygons);
                cout << result << endl;
            }
            else if (param == "ODD")
            {
                int result = geometry::count_odd_vertexes(polygons);
                cout << result << endl;
            }
            else
            {
                int num;
                istringstream(param) >> num;
                if (num > 0)
                {
                    int result = geometry::count_specific_vertexes(polygons, num);
                    cout << result << endl;
                }
                else
                {
                    cout << "<INVALID COMMAND>" << endl;
                }
            }
        }
        else if (cmd == "RECTS")
        {
            int result = geometry::count_rectangles(polygons);
            cout << result << endl;
        }
        else if (cmd == "MAXSEQ")
        {
            string polygonDesc;
            getline(iss, polygonDesc);
            int result = geometry::max_sequence_of_polygon(polygons, polygonDesc);
            if (result >= 0)
            {
                cout << result << endl;
            }
            else
            {
                cout << "<INVALID COMMAND>" << endl;
            }
        }
        else
        {
            cout << "<INVALID COMMAND>" << endl;
        }
    }

    return 0;
}

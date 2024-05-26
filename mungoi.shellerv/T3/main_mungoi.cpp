#include <iostream>
#include <vector>
#include "struct_mungoi.h"
#include "polygon_mungoi.h"

int main()
{
    std::vector<mungoisheller::Polygon> polygons;
    mungoisheller::Polygon polygon;
    while (std::cin >> polygon)
    {
        polygons.push_back(polygon);
    }
    std::map<std::string, std::function<void(const std::vector<mungoisheller::Polygon>&, std::istream&, std::ostream&)>> command_map = {
      {"AREA", mungoisheller::area_param},
      {"MAX", mungoisheller::max_param},
      {"MIN", mungoisheller::min_param},
      {"COUNT", mungoisheller::count_param},
      {"RECTS", mungoisheller::rects_param},
      {"MAXSEQ", mungoisheller::maxseq_param}
    };

    std::string command;
    while (std::cin >> command)
    {
        if (command_map.find(command) != command_map.end())
        {
            command_map[command](polygons, std::cin, std::cout);
        }
        else
        {
            std::cout << "Invalid command\n";
        }
    }
    return 0;
}

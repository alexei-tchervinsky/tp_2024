#include "functions.hpp"
#include <algorithm>
#include <limits>
#include <exception>
#include <map>
#include <functional>

using namespace geometry;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "FILENAME_NOT_SPECIFIED\n";
        return 1;
    }
    std::ifstream in;
    in.open(argv[1]);
    if (!in)
    {
        std::cerr << "FILE_NOT_FOUND\n";
        return 1;
    }
    std::vector< geometry::Polygon > polygons;
    while (!in.eof())
    {
        std::copy(std::istream_iterator< geometry::Polygon >(in),
        std::istream_iterator< geometry::Polygon >(),
        std::back_inserter(polygons));
        if (in.fail())
        {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::map< std::string, std::function< void(const std::vector< geometry::Polygon >, std::istream &, std::ostream &) > > commands
    {
        {"AREA", geometry::area_param},
        {"MAX", geometry::max_param},
        {"MIN", geometry::min_param},
        {"COUNT", geometry::count_param},
        {"RECTS", geometry::rects_param},
        {"MAXSEQ", geometry::maxseq_param}
    };

    std::cout << std::fixed;
    while (!std::cin.eof())
    {
        try
        {
            std::string key;
            std::cin >> key;
            if (commands.find(key) != commands.end())
            {
                auto command = std::bind(commands[key], std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                command(polygons, std::cin, std::cout);
            }
            else if (!std::cin.eof())
            {
                throw std::invalid_argument("<INVALID COMMAND>");
            }
        }
        catch (const std::exception& ex)
        {
            std::cout << ex.what() << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return 0;
}

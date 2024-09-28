#include "Geometry.h"
#include <algorithm>
#include <limits>
#include <exception>
#include <map>
#include <functional>
#include <iterator>

using namespace Geometry;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "FILENAME_NOT_SPECIFIED\n";
        return 1;
    }

    std::ifstream inFile(argv[1]);

    if (!inFile) {
        std::cerr << "FILE_NOT_FOUND\n";
        return 1;
    }

    std::vector<Polygon> polygons;

    while (!inFile.eof()) {
        std::copy(std::istream_iterator<Polygon>(inFile),
                  std::istream_iterator<Polygon>(),
                  std::back_inserter(polygons));
        if (inFile.fail()) {
            inFile.clear();
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::map<std::string, std::function<void(const std::vector<Polygon> &, std::istream &, std::ostream &)>> commands
            {
                    {"AREA",          areaParam},
                    {"MAX",           maxParam},
                    {"MIN",           minParam},
                    {"COUNT",         countParam},
                    {"LESSAREA",      lessAreaParam},
                    {"INTERSECTIONS", intersectionsParam}
            };

    std::cout << std::fixed;

    while (!std::cin.eof()) {
        try {
            std::string key;
            std::cin >> key;
            if (commands.find(key) != commands.end()) {
                commands[key](polygons, std::cin, std::cout);
            } else if (!std::cin.eof()) {
                throw std::invalid_argument("<INVALID COMMAND>");
            }
        }
        catch (const std::exception &ex) {
            std::cout << ex.what() << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return 0;
}

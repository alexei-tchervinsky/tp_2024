#include <iostream>
#include <fstream>
#include <iterator>
#include <limits>
#include <algorithm>
#include <map>
#include <functional>

#include "Polygon.hpp"
#include "Commands.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Error: wrong number of arguments.\n";
    return 2;
  }

  std::ifstream file(argv[1]);
  if (!file) {
    std::cerr << "Error: cannot open the file.\n";
    return 3;
  }

  std::vector<shapes::Polygon> polygons;
  while (!file.eof()) {
    std::copy(
        std::istream_iterator<shapes::Polygon>(file),
        std::istream_iterator<shapes::Polygon>(),
        std::back_inserter(polygons)
    );
    if (file.fail() && !file.eof()) {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  // testing testing
  std::cout << "Polygons:\n";
  std::cout << "size: " << polygons.size() << '\n';
  std::cout << "====================\n";
  std::copy(
      polygons.begin(),
      polygons.end(),
      std::ostream_iterator<shapes::Polygon>{std::cout, ""}
  );

  std::map<std::string, std::function<std::ostream&(const std::vector<shapes::Polygon>&, std::istream &, std::ostream &)> > cmds;
  {
    cmds["AREA"] = std::bind(commands::getArea, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cmds["MAX"] = std::bind(commands::getMax, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cmds["MIN"] = std::bind(commands::getMin, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cmds["COUNT"] = std::bind(commands::countShapes, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  }

  return 0;
}

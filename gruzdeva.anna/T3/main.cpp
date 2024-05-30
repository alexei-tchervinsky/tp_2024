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

  std::map<std::string, std::function<std::ostream&(std::vector<shapes::Polygon>&, std::istream &, std::ostream &)> > cmds;
  {
    cmds["AREA"] = std::bind(commands::getArea, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cmds["MAX"] = std::bind(commands::getMax, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cmds["MIN"] = std::bind(commands::getMin, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cmds["COUNT"] = std::bind(commands::countShapes, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cmds["ECHO"] = std::bind(commands::echo, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cmds["INFRAME"] = std::bind(commands::inFrame, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  }

  std::string cmd = "";
  while (std::cin >> cmd) {
    try {
      cmds.at(cmd)(polygons, std::cin, std::cout);
    }
    catch (const std::invalid_argument& ex) {
      commands::outError(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error& ex) {
      commands::outError(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}

#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <map>
#include <functional>
#include <limits>
#include "commands.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Error: incorrect number of arguments.";
    return 2;
  }
  std::ifstream input(argv[1]);
  if (!input) {
    std::cerr << "Error: the file cannot be opened.";
    return 2;
  }

  std::vector< ananjeva::Polygon > shapes;

  while (!input.eof()) {
    std::copy(
      std::istream_iterator< ananjeva::Polygon >(input),
      std::istream_iterator< ananjeva::Polygon >(),
      std::back_inserter(shapes)
    );
    if (input.fail() && !input.eof()) {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function < std::ostream& (std::vector < ananjeva::Polygon >&, std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(ananjeva::getAreas, _1, _2, _3);
    cmds["MAX"] = std::bind(ananjeva::getMax, _1, _2, _3);
    cmds["MIN"] = std::bind(ananjeva::getMin, _1, _2, _3);
    cmds["COUNT"] = std::bind(ananjeva::countShapes, _1, _2, _3);
    cmds["INFRAME"] = std::bind(ananjeva::checkInFrame, _1, _2, _3);
  }

  std::string cmd = "";
  while (std::cin >> cmd) {
    try {
      cmds.at(cmd)(shapes, std::cin, std::cout);
    }
    catch (const std::out_of_range&) {
      ananjeva::outError(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error&) {
      ananjeva::outError(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}

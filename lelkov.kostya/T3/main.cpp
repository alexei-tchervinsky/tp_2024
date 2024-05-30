#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <iterator>
#include <limits>
#include "struct.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace lelkov;
  if (argc != 2)
  {
    std::cerr << "< INVALID NUMBER OF ARGUMENTS >\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "< UNABLE TO READ FILE >\n";
    return 2;
  }
  std::vector< Polygon > allPolygons;
  while (!in.eof())
  {
    std::copy
    (
      std::istream_iterator< Polygon >(in),
      std::istream_iterator< Polygon >(),
      std::back_inserter(allPolygons)
    );
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function < void(std::vector< Polygon >&, std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(commandArea, _1, _2, _3);
    commands["MAX"] = std::bind(commandMax, _1, _2, _3);
    commands["MIN"] = std::bind(commandMin, _1, _2, _3);
    commands["COUNT"] = std::bind(commandCount, _1, _2, _3);
    commands["RECTS"] = std::bind(commandRects, _1, _3);
    commands["SAME"] = std::bind(commandSame, _1, _2, _3);
  }
  std::string inputCommand = {};
  while (std::cin >> inputCommand)
  {
    try
    {
      commands.at(inputCommand)(allPolygons, std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      lelkov::outError(std::cout, "INVALID COMMAND");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <map>
#include <iterator>
#include <functional>

#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, const char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Wrong input" << '\n';
    return 9;
  }
  
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "Wrong input" << '\n';
    return 9;
  }
  
  using namespace gredasov;
  std::vector< Polygon > polygons;
  while (!in.eof())
  {
    std::copy(std::istream_iterator< Polygon >(in), std::istream_iterator< Polygon >(), std::back_inserter(polygons));
    if (in.fail() && !in.eof())
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  
  std::map< std::string, std::function< void(const std::vector< Polygon > & polygons, std::ostream & out, std::istream & is) > > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(gredasov::getAreaCommand, _1, _2, _3);
    commands["MAX"] = std::bind(gredasov::getMaxCommand, _1, _2, _3);
    commands["MIN"] = std::bind(gredasov::getMinCommand, _1, _2, _3);
    commands["COUNT"] = std::bind(gredasov::getCountCommand, _1, _2, _3);
    commands["INFRAME"] = std::bind(gredasov::isInFrameCommand, _1, _2, _3);
    commands["INTERSECTIONS"] = std::bind(gredasov::getIntersectionsCommand, _1, _2, _3);
  }

  std::string c;
  while (std::cin >> c)
  {
    try
    {
      commands.at(c)(polygons, std::cout, std::cin);
    }
    catch(const std::out_of_range & e)
    {
      gredasov::outputMessage(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  
  return 0;
}


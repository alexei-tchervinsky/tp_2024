#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>
#include <map>
#include <functional>
#include "geometryShapes.hpp"
#include "commands.hpp"

using namespace std::placeholders;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Wrong amount of arguments\n";
    return 1;
  }
  std::vector<leontiev::Polygon> polygons;
  std::ifstream input(argv[1]);
  while (!input.eof())
  {
    std::copy(std::istream_iterator<leontiev::Polygon>{input}, std::istream_iterator<leontiev::Polygon>{}, std::back_inserter(polygons));
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::map<std::string, std::function <std::ostream & (std::istream &, std::ostream &, const std::vector<leontiev::Polygon> &)>> commands;
  commands["AREA"] = std::bind(leontiev::calculateArea, _3, _2, _1);
  commands["MAX"] = std::bind(leontiev::getMax, _3, _2, _1);
  commands["MIN"] = std::bind(leontiev::getMin, _3, _2, _1);
  commands["COUNT"] = std::bind(leontiev::count, _3, _2, _1);

  std::string argument = "";
  while (std::cin >> argument)
  {
    try
    {
      commands.at(argument)(std::cin, std::cout, polygons);
    }
    catch(const std::out_of_range& e)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    catch(const std::logic_error& e)
    {
      std::cout << "<INVALID COMMAND>" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

  }

  return 0;
}
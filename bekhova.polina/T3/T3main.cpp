﻿#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <limits>
#include <functional>
#include <iterator>
#include "commands.h"

using namespace bekhova;
int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: wrong input\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  std::vector<Polygon> polygons;
  while (!input.eof())
  {
    std::copy(
      std::istream_iterator<Polygon>{input},
      std::istream_iterator<Polygon>{},
      std::back_inserter(polygons));
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::map<std::string, std::function<void(std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)>> commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(bekhova::Area, _1, _2, _3);
    commands["MAX"] = std::bind(bekhova::Max, _1, _2, _3);
    commands["MIN"] = std::bind(bekhova::Min, _1, _2, _3);
    commands["COUNT"] = std::bind(bekhova::Count, _1, _2, _3);
    commands["PERMS"] = std::bind(bekhova::Perms, _1, _2, _3);
    commands["RIGHTSHAPES"] = std::bind(bekhova::Rightshapes, _1, _2);
  }

  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string parameter;
  while (std::cin >> parameter)
  {
    try
    {
      commands.at(parameter)(polygons, std::cout, std::cin);
    }
    catch (const std::out_of_range& ex)
    {
      outInvalid(std::cout);
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}

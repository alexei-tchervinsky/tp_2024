
#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <unordered_map>
#include <limits>

#include "coms.hpp"

int main()
{
  using dictionary = std::unordered_map< std::string, std::size_t >;
  using dictionaries = std::map< std::string, dictionary >;
  dictionaries dicts;
  std::map< std::string, std::function< void(dictionaries& dicts, std::ostream& out, std::istream& in) > > commands;
  {
    using namespace std::placeholders;
    commands["HELP"] = std::bind(mynspace::getHelp, _2, _3);
    commands["CREATE"] = std::bind(mynspace::create, _1, _2, _3);
    commands["SHOW"] = std::bind(mynspace::showDictionary, _1, _2, _3);
    commands["TOP"] = std::bind(mynspace::showTop, _1, _2, _3);
    commands["SEARCH"] = std::bind(mynspace::search, _1, _2, _3);
    commands["DELETE"] = std::bind(mynspace::deleteDict, _1, _2, _3);
    commands["INTERSECTIONS"] = std::bind(mynspace::getIntersections, _1, _2, _3);
    commands["MERGE"] = std::bind(mynspace::merge, _1, _2, _3);
    commands["ALL"] = std::bind(mynspace::getAll, _1, _2, _3);
    commands["SAVE"] = std::bind(mynspace::save, _1, _2, _3);
    commands["SORT"] = std::bind(mynspace::sort, _1, _2, _3);
  }

  std::cout << "type <HELP> to see availible commands\n";

  std::string c;
  while (std::cin >> c)
  {
    try
    {
      commands.at(c)(dicts, std::cout, std::cin);
    }
    catch (const std::exception& e)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}

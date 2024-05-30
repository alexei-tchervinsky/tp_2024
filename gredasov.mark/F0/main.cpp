#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <unordered_map>
#include <limits>

#include "commands.hpp"

int main()
{
  using dictionary = std::unordered_map< std::string, std::size_t >;
  using dictionaries = std::map< std::string, dictionary >;
  dictionaries dicts;
  std::map< std::string, std::function< void(dictionaries& dicts, std::ostream& out, std::istream& in) > > commands;
  {
    using namespace std::placeholders;
    commands["HELP"] = std::bind(gredasov::getHelpCommand, _2, _3);
    commands["CREATE"] = std::bind(gredasov::createCommand, _1, _2, _3);
    commands["SHOW"] = std::bind(gredasov::showDictionaryCommand, _1, _2, _3);
    commands["TOP"] = std::bind(gredasov::showTopCommand, _1, _2, _3);
    commands["SEARCH"] = std::bind(gredasov::searchCommand, _1, _2, _3);
    commands["DELETE"] = std::bind(gredasov::deleteCommand, _1, _2, _3);
    commands["INTERSECTIONS"] = std::bind(gredasov::getIntersectionsCommand, _1, _2, _3);
    commands["MERGE"] = std::bind(gredasov::mergeCommand, _1, _2, _3);
    commands["ALL"] = std::bind(gredasov::getAllCommand, _1, _2, _3);
    commands["SAVE"] = std::bind(gredasov::saveCommand, _1, _2, _3);
    commands["SORT"] = std::bind(gredasov::sortCommand, _1, _2, _3);
  }

  std::cout << "type <HELP> to see availible commands\n";

  std::string c;
  while (std::cin >> c)
  {
    try
    {
      commands.at(c)(dicts, std::cout, std::cin);
    }
    catch(const std::exception& e)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}


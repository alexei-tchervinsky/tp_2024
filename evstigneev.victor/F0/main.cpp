#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <functional>
#include "commands.hpp"

int main()
{
  std::unordered_map<std::string, std::size_t> dict;
  std::unordered_map <std::string,
    std::function<void(evstigneev::dictionary&, std::istream&, std::ostream&)>> cmd;
  cmd["HELP"] = std::bind(evstigneev::help, std::placeholders::_3);
  cmd["CREATE"] = std::bind(evstigneev::create, std::placeholders::_1, std::placeholders::_2,
    std::placeholders::_3);
  cmd["TOP"] = std::bind(evstigneev::top, std::placeholders::_1, std::placeholders::_2,
    std::placeholders::_3);
  cmd["FIND"] = std::bind(evstigneev::find, std::placeholders::_1, std::placeholders::_2,
    std::placeholders::_3);
  cmd["MERGE"] = std::bind(evstigneev::merge, std::placeholders::_1, std::placeholders::_2,
    std::placeholders::_3);
  cmd["REMOVE"] = std::bind(evstigneev::remove, std::placeholders::_3);
  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      cmd.at(command)(dict, std::cin, std::cout);
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <functional>
#include "commands.h"

int main()
{
  std::cout << "If you need help, write a 'HELP' \n";
  std::map<std::string, std::size_t> dict;
  std::map <std::string,
    std::function<void(bekhova::dictionary&, std::istream&, std::ostream&)>> cmd;
  cmd["HELP"] = std::bind(bekhova::help, std::placeholders::_3);
  cmd["CREATE"] = std::bind(bekhova::create, std::placeholders::_1, std::placeholders::_2,
    std::placeholders::_3);
  cmd["TOP"] = std::bind(bekhova::top, std::placeholders::_1, std::placeholders::_2,
    std::placeholders::_3);
  cmd["FIND"] = std::bind(bekhova::find, std::placeholders::_1, std::placeholders::_2,
    std::placeholders::_3);
  cmd["MERGE"] = std::bind(bekhova::merge, std::placeholders::_1, std::placeholders::_2,
    std::placeholders::_3);
  cmd["REMOVE"] = std::bind(bekhova::remove, std::placeholders::_1, std::placeholders::_3);
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

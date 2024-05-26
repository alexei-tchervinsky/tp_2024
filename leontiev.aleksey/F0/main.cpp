#include <iostream>
#include <map>
#include <string>
#include <functional>
#include "commands.hpp"
using namespace std::placeholders;

int main()
{
  std::cout << "It is a Frequancy Dictionary. Use 'help' to see all the commands\n";
  std::unordered_map<std::string, std::size_t> frDict;

  std::unordered_map<std::string, std::function<void(std::unordered_map<std::string, std::size_t>&, std::istream&, std::ostream&)>> commands;
  commands["help"] = std::bind(leontiev::help, _3);
  commands["create"] = std::bind(leontiev::create, _1, _2, _3);
  commands["display"] = std::bind(leontiev::display, _1, _2, _3);
  commands["top"] = std::bind(leontiev::top, _1, _2, _3);


  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(frDict, std::cin, std::cout);
    }
    catch (std::exception& e)
    {
      std::cerr << e.what() << "\n";
    }
  }

  return 0;
}
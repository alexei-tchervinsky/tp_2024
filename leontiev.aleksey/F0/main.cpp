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
  commands["display"] = std::bind(leontiev::display, _1, _3);
  commands["top"] = std::bind(leontiev::top, _1, _2, _3);
  commands["findW"] = std::bind(leontiev::findWord, _1, _2, _3);
  commands["clear"] = std::bind(leontiev::clear, _1, _3);
  commands["merge"] = std::bind(leontiev::merge, _1, _2, _3);
  commands["findN"] = std::bind(leontiev::findN, _1, _2, _3);
  commands["out"] = std::bind(leontiev::out, _1, _2, _3);

  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(frDict, std::cin, std::cout);
    }
    catch (std::out_of_range& e)
    {
      std::cout << "Invalid command\n";
    }
    catch (std::logic_error& e)
    {
      std::cerr << e.what() << "\n";
    }
  }

  return 0;
}

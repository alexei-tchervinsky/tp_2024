#include <iostream>
#include <map>
#include <string>
#include <functional>
#include "commands.hpp"

int main()
{
  std::cout << "--------- Frequency Dictionary ---------\n";
  std::cout << "Type 'commands' to view list of available commands.\n";

  using namespace std::placeholders;
  std::unordered_map<std::string, std::size_t> frequencyDict;

  std::unordered_map<std::string, std::function<void(std::unordered_map<std::string, std::size_t> &, std::istream &, std::ostream &)>> commands;
  commands["commands"] = std::bind(semzin::commands, _3);
  commands["make"] = std::bind(semzin::make, _1, _2, _3);
  commands["sortMtoL"] = std::bind(semzin::sortMtoL, _1, _2, _3);
  commands["sortLtoM"] = std::bind(semzin::sortLtoM, _1, _2, _3);
  commands["print"] = std::bind(semzin::print, _1, _3);
  commands["holyTrinityMost"] = std::bind(semzin::holyTrinityMost, _1, _2, _3);
  commands["holyTrinityLeast"] = std::bind(semzin::holyTrinityLeast, _1, _2, _3);
  commands["find"] = std::bind(semzin::findWord, _1, _2, _3);
  commands["remove"] = std::bind(semzin::removeWord, _1, _2, _3);
  commands["deleteDict"] = std::bind(semzin::remove, _1, _3);
  commands["save"] = std::bind(semzin::save, _1, _2, _3);

  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(frequencyDict, std::cin, std::cout);
    }
    catch (std::out_of_range &ex)
    {
      std::cerr << "Invalid command!\n\n";
    }
    catch (std::logic_error &ex)
    {
      std::cerr << ex.what() << "\n\n";
    }
  }

  return 0;
}
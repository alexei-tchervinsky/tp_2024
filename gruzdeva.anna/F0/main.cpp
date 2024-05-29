#include <memory>
#include <functional>
#include <map>
#include <string>
#include <iostream>
#include <limits>

#include "Commands.hpp"

using cmdFunc = std::function<void(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>&,
    std::string&, std::istream&, std::ostream&)>;

int main() {
  std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>> dictionaries;
  std::string currentDict = "default";
  std::map<std::string, cmdFunc> cmds;
  {
    cmds["HELP"] = std::bind(commands::help, std::placeholders::_4);
    cmds["LIST"] = std::bind(commands::getAllDictionaries, std::placeholders::_1, std::placeholders::_4);
    cmds["CREATE"] = std::bind(commands::create, std::placeholders::_1, std::placeholders::_2,
                               std::placeholders::_3, std::placeholders::_4);
    cmds["RENAME"] = std::bind(commands::rename, std::placeholders::_1, std::placeholders::_2
                               std::placeholders::_3, std::placeholders::_4);
    cmds["DELETE"] = std::bind(commands::del, std::placeholders::_1, std::placeholders::_3, std::placeholders::_4);
    cmds["USE"] = std::bind(commands::changeCurrentDictionary, std::placeholders::_1, std::placeholders::_2,
                            std::placeholders::_3, std::placeholders::_4);
    cmds["COUNT"] = std::bind(commands::count, std::placeholders::_1, std::placeholders::_2, std::placeholders::_4);
    cmds["PRINT"] = std::bind(commands::print, std::placeholders::_1, std::placeholders::_2, std::placeholders::_4);
    cmds["SEARCH"] = std::bind(commands::search, std::placeholders::_1, std::placeholders::_2,
                               std::placeholders::_3, std::placeholders::_4);
    cmds["REMOVE"] = std::bind(commands::remove, std::placeholders::_1, std::placeholders::_2,
                               std::placeholders::_3, std::placeholders::_4);
    cmds["SAVE"] = std::bind(commands::save, std::placeholders::_1, std::placeholders::_2,
                             std::placeholders::_3, std::placeholders::_4);
  }

  std::string cmd;
  std::cout << "Enter \"HELP\" to see the list of available commands.\n";
  while (std::cin >> cmd) {
    try {
      cmds.at(cmd)(dictionaries, currentDict, std::cin, std::cout);
    }
    catch (const std::invalid_argument& ex) {
      commands::outError(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error& ex) {
      commands::outError(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}

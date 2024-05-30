#include "commands.hpp"
#include <iostream>
#include <map>
#include <limits>
#include <string>
#include <functional>

int main() {
  setlocale(LC_ALL, "Russian");

  using mapOfDicts = std::map< std::string, std::map< std::string, std::set< std::string > > >;

  mapOfDicts Dicts;

  std::map< std::string, std::function< void(mapOfDicts&, std::istream&, std::ostream&) > > command;
  {
    using namespace std::placeholders;
    command["info"] = std::bind(berezneva::info, _3);
    command["create"] = std::bind(berezneva::create, _1, _2, _3);
    command["remove"] = std::bind(berezneva::create, _1, _2, _3);
    command["search"] = std::bind(berezneva::create, _1, _2, _3);
    command["rename"] = std::bind(berezneva::rename, _1, _2, _3);
    command["names"] = std::bind(berezneva::allDictNames, _1, _3);
    command["count"] = std::bind(berezneva::countWords, _1, _2, _3);
  }

  std::cout << "Enter 'info' to see available commands.\n";

  std::string cmd;
  while (std::cin >> cmd) {
    try {
      command.at(cmd) (Dicts, std::cin, std::cout);
    }
    catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}

#include "commands.hpp"
#include <iostream>
#include <map>
#include <limits>
#include <string>
#include <functional>

int main() {
  setlocale(LC_ALL, "Russian");

  using dictType = std::pair< std::string, std::map< std::string, std::set< std::string > > >;
  using mapOfDictionaries = std::map< std::string, std::map< std::string, std::set< std::string > > >;

  mapOfDictionaries allDictionaries;

  std::map< std::string, std::function< void (mapOfDictionaries&, std::istream&, std::ostream&) > > command;
  {
    using namespace std::placeholders;
    command["help"] = std::bind(ananjeva::printCommands, _3);
    command["create"] = std::bind(ananjeva::createDict, _1, _2, _3);
    command["rename"] = std::bind(ananjeva::renameDict, _1, _2, _3);
    command["list"] = std::bind(ananjeva::listAllDict, _1, _3);
    command["print"] = std::bind(ananjeva::printDict, _1, _2, _3);
    command["count"] = std::bind(ananjeva::countWordsInDict, _1, _2, _3);
    command["unite"] = std::bind(ananjeva::uniteDictionaries, _1, _2, _3);
  }

  std::cout << "Enter 'help' to get the list of all available commands.\n";

  std::string cmd = "";
  while (std::cin >> cmd) {
    try {
      command.at(cmd) (allDictionaries, std::cin, std::cout);
    }
    catch (const std::out_of_range&) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
        catch (const std::invalid_argument&) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error&) {
      std::cerr << "Invalid command.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      return 2;
    }
    catch (const std::exception& ex) {
      std::cerr << ex.what() << '\n';
      return 2;
    }

  }

  return 0;
}

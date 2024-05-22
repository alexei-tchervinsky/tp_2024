#include "commands.hpp"
#include "selectedDictionary.hpp"
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

  ananjeva::SelectedDictionary selDict;

  std::map< std::string, std::function< void (mapOfDictionaries&, std::istream&, std::ostream&) > > command;
  {
    using namespace std::placeholders;
    command["help"] = std::bind(ananjeva::printCommands, _3);
    command["create"] = std::bind(ananjeva::createDict, _1, _2, _3);
    command["rename"] = std::bind(ananjeva::renameDict, _1, _2, _3);
    command["list"] = std::bind(ananjeva::listAllDict, _1, _3);
    command["print"] = std::bind(ananjeva::printDict, _1, _2, _3);
    command["count"] = std::bind(ananjeva::countWordsInDict, _1, _2, _3);
    command["add"] = std::bind(ananjeva::addDictToDict, _1, _2, _3);
    command["unite"] = std::bind(ananjeva::uniteDictionaries, _1, _2, _3);
    command["remove"] = std::bind(ananjeva::removeDict, _1, _2, _3);
    command["select"] = std::bind(&ananjeva::SelectedDictionary::selectDict, &selDict, _1, _2, _3);
    command["insert"] = std::bind(&ananjeva::SelectedDictionary::insertDict, &selDict, _1, _2, _3);
    command["find"] = std::bind(&ananjeva::SelectedDictionary::findWordInDict, &selDict, _1, _2, _3);
    command["delete_word"] = std::bind(&ananjeva::SelectedDictionary::deleteWordInDict, &selDict, _1, _2, _3);
  }

  std::cout << "Enter 'help' to get the list of all available commands.\n";

  std::string cmd = "";
  while (std::cin >> cmd) {
    try {
      command.at(cmd) (allDictionaries, std::cin, std::cout);
    }
    /*catch (const std::out_of_range&) {
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
    }*/
    catch (const std::exception& ex) {
      std::cerr << ex.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      return 2;
    }

  }

  return 0;
}

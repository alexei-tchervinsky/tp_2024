#include "Commands.hpp"

int main()
{
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > >
  dict(new std::pair<std::string, std::map< std::string, std::set<std::string> > >);
  dict->first = "";
  std::map< std::string, std::function< void(
  std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > >,
  std::istream &,
  std::ostream &) > > commands
  {
    {"HELP", commands::HELP},
    {"OPEN", commands::OPEN},
    {"CLOSE", commands::CLOSE},
    {"COMPARE", commands::COMPARE},
    {"MERGE", commands::MERGE},
    {"INSERT", commands::INSERT},
    {"DELETE", commands::DELETE},
    {"SEARCH", commands::SEARCH},
    {"CHANGE", commands::CHANGE},
    {"SHOW", commands::SHOW},
    {"SHOWALL", commands::SHOWALL}
  };
  std::cout << std::fixed;
  setlocale(LC_ALL, "Russian");
  std::cout <<
  "#####################################################################################\n\
  Это Англо-русский словарь Ананьева Артема:\n\
  Команда HELP:\n\
  1.'HELP' выводит данный сценарий;\n\
  2.'HELP COMMAND' выводит сценарий с описанием встроенных команд;\n\
  3.'HELP INFO' выводит сценарий с описанием открытого словаря\n";
  std::cout <<
  "#####################################################################################\n";
  while (!std::cin.eof())
  {
    try
    {
      std::string key;
      std::cin >> key;
      if (commands.find(key) != commands.end())
      {
        auto command = std::bind(commands[key], std::placeholders::_1, std::placeholders::_2,
        std::placeholders::_3);
        command(dict, std::cin, std::cout);
      }
      else if (!std::cin.eof())
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
    catch (const std::exception& ex)
    {
      std::cout << ex.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}

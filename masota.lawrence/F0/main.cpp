// LabF0main.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "New_lawdict.h"

int main()
{
    std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > >
        dict(new std::pair<std::string, std::map< std::string, std::set<std::string> > >);
    dict->first = "";
    std::map< std::string, std::function< void(
        std::shared_ptr< std::pair<std::string, std::map< std::string, std::set<std::string> > > >,
        std::istream&,
        std::ostream&) > > commands
    {
      {"HELP", dictcommands::HELP},
      {"OPEN", dictcommands::OPEN},
      {"CLOSE", dictcommands::CLOSE},
      {"COMPARE", dictcommands::COMPARE},
      {"MERGE", dictcommands::MERGE},
      {"INSERT", dictcommands::INSERT},
      {"DELETE", dictcommands::DELETE},
      {"SEARCH", dictcommands::SEARCH},
      {"CHANGE", dictcommands::CHANGE},
      {"SHOW", dictcommands::SHOW},
      {"SHOWALL", dictcommands::SHOWALL}
    };
    std::cout << std::fixed;
    setlocale(LC_ALL, "Russian");
    std::cout <<
        "######################################################################################\n" <<
        "Welcome to Lawrence's English-Russian dictionary:\n" <<
        "HELP command:\n" <<
        "1.'HELP' displays this script;\n" <<
        "2.'HELP COMMAND' displays a script describing the built-in commands;\n" <<
        "3.'HELP INFO' displays a script describing the open dictionary\n";
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

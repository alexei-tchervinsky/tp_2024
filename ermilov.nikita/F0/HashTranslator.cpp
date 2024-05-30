#ifdef _WIN32
#include <Windows.h>
#include <stdio.h>
#endif

#ifdef __unix__
#include <unistd.h>
#include <stdlib.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <limits>
#include <functional>
#include "functions.h"

typedef std::unordered_multimap<std::string, std::list<std::string>>::iterator unit;
typedef std::unordered_multimap<std::string, std::list<std::string>> stringMap;
using namespace ermilov;

int main(int argc, char** argv)
{
  std::cout << "====================================" << '\n';
  std::cout << "     Hash Translator Eng - Rus" << '\n';
  std::cout << "====================================" << '\n';

#ifdef _WIN32
  setlocale(LC_ALL, "russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
#endif

  if (argc != 2) {
    std::cerr << "BAD PARAMETERS" << '\n';
    return -1;
  }
  std::string fileName = argv[1];

  std::ifstream file;
  file.open(fileName);
  std::unordered_multimap<std::string, std::list<std::string>> translator;

  std::string eng, rus;

  std::cout << '\n' << "Loading translates...\n";
  if (file.is_open())
  {
    while (!file.eof())
    {
      file >> eng >> rus;
      if (!correctEng(eng) || !correctRus(rus))
      {
        std::cout << "Error! Incorrect word: " << eng << "!\n";
      }
      else
      {
        auto found = translator.find(eng);
        if (found != translator.end())
        {
          found->second.push_back(rus);
          found->second.sort();
        }
        else
        {
          std::list<std::string> tranlates;
          tranlates.push_back(rus);
          std::pair<std::string, std::list<std::string>> pair(eng, tranlates);
          translator.insert(pair);
        }

      }
    }
    file.close();
    std::cout << "Loaded " << translator.size() << " words!\n\n";

  }
  else
  {
    std::cout << "Error! Could not open file!\n";
    return -1;
  }

  std::cout << "To add a new word, type INSERT <word> <any amount of translates>.\n";
  std::cout << "To delete a word, type REMOVE <word>.\n";
  std::cout << "To translate the word, enter TRANSLATE <word>.\n\n";

  std::map <std::string,
    std::function<void(stringMap&, std::istream&, std::ostream&)>> commands;
  {
    commands["INSERT"] = insert;
    commands["REMOVE"] = deleteWord;
    commands["TRANSLATE"] = translate;
  }

  std::string word;

  while (!std::cin.eof())
  {
    try
    {
      std::cin >> word;
      commands.at(word)(translator, std::cin, std::cout);
    }
    catch (std::exception& e)
    {
      std::cerr << "<INVALID COMMAND>\n\n";
      std::cin.clear();
      std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }

  }
}

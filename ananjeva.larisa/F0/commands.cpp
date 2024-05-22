#include "commands.hpp"
#include <fstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <limits>
#include <exception>

void ananjeva::printCommands(std::ostream& out) {
  out << "=========================================================================\n"
  << "Команды англо-русского словаря:\n"
  << "1. help - вывод списка доступных команд с параметрами;\n"
  << "2. create <filName.txt> - создание словаря из файла .txt с именем <fileName>\n"
  << " или create <dict. name> - создание словаря указанного пользователем имени;\n"
  << "3. rename <old dict. name> <new dict. name> - переименование словаря с"
  << " <old dict. name> на <new dict. name>;\n"
  << "4. list - вывод названий всех существующих словарей;\n"
  << "5. print <dict. name> - вывод словаря <dict. name>;\n"
  << "6. count <dict. name> - вывод количества слов в словаре <dict. name>;\n"
  << "7. add <dict.1> <dict.2> - добавление словаря <dict.1> в словарь <dict.2>;\n"
  << "8. unite <new dict.> <dict.1> <dict.2> - объединение словарей <dict.1> и \n"
  << " <dict.2> в новый словарь <new dict.>;\n"
  << "9. remove <dict. name> - удаление словаря <dict. name>;\n"
  << "10. select <dict. name> - выбор словаря, для которого будут \n"
  << "производиться следующие команды;\n"
  << "Перед использованием команд 11, 12, 13 нужно с помощью команды 10\n"
  << "выбрать словарь, к которому буду применяться следующие действия.\n"
  << "11. insert {eng - rus; rus; ...} - вставка в словарь слова и его перевода\n"
  << "Например: insert {cat - кот; кошка}\n"
  << "12. find <word> - вывод перевода слова <word>;\n"
  << "13. delete_word <word> - удаление слова <word> и его переводов из словаря;\n"
  << "=========================================================================\n";
}


dictTypeWithoutName ananjeva::getDictFromInput(std::istream& in) {
  dictTypeWithoutName inputDictionary;
  //std::vector< DictIO > dictionary;
  DictIO newPair;

  while (!in.eof()) {
    /*std::copy(
      std::istream_iterator< DictIO >(in),
      std::istream_iterator< DictIO >(),
      std::back_inserter(dictionary)
    );*/
    in >> newPair;
    if (in.fail() && !in.eof()) {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    inputDictionary[newPair.dictStr.first] = newPair.dictStr.second;
  }
  /*for (auto& element : dictionary) {
    inputDictionary[element.dictStr.first] = element.dictStr.second;
  }*/
  return inputDictionary;
}

void ananjeva::createDict(mapOfDictionaries& allDictionaries, std::istream& in, std::ostream& out) {
  std::string name = "";
  in >> name;
  if (allDictionaries.find(name) != allDictionaries.cend()) {
    throw std::invalid_argument("Such dictionary already exists.");
  }
  else {
    if (name.find(".txt") != std::string::npos) {
      std::string fileName = name;
      std::ifstream input;
      input.open(fileName);

      if (input.is_open()) {
        std::size_t start {fileName.find(".txt")};
        std::string dictName = fileName.replace(start, start + 4, "");
        dictTypeWithoutName dictionary = ananjeva::getDictFromInput(input);
        allDictionaries.emplace(dictName, dictionary);
        out << "New dictionary <" << dictName << "> was created from file.\n";
      }
      else {
        throw std::out_of_range("File isn't opened.");
      }
      input.close();
    }
    else {
      dictTypeWithoutName dictionary {};
      allDictionaries.emplace(name, dictionary);
      out << "New dictionary <" << name << "> was created.\n";
    }
  }
}

void ananjeva::renameDict(mapOfDictionaries& allDictionaries, std::istream& in, std::ostream& out) {
  std::string oldName = "";
  std::string newName = "";
  in >> oldName;
  in >> newName;
  if (allDictionaries.find(newName) == allDictionaries.end()) {
    auto dictOldNameIt = allDictionaries.find(oldName);
    allDictionaries.emplace(newName, dictOldNameIt->second);
    allDictionaries.erase(dictOldNameIt);
    out << "Dictionary '" << oldName << "' was renamed to '" << newName << "' successfully.\n";
  }
  else {
    out << "Dictionary with name '" << oldName << "' wasn't found.\n";
  }
}

void ananjeva::listAllDict(mapOfDictionaries& allDictionaries, std::ostream& out) {
  if (allDictionaries.empty()) {
    out << "There is no one dictionary.\n";
  }
  else {
    std::size_t dictNum = 1;
    for (auto it = allDictionaries.begin(); it != allDictionaries.end(); ++it) {
      out << dictNum << ". " << it->first << '\n';
      ++dictNum;
    }
  }
}

void ananjeva::printDict(mapOfDictionaries& allDictionaries, std::istream& in, std::ostream& out) {
  std::string dictName = "";
  in >> dictName;
  if (dictName == "") {
    throw std::invalid_argument("No one dictionary was chosen.");
  }
  if (allDictionaries.count(dictName) == 1) {
    dictTypeWithoutName nessDict = allDictionaries.find(dictName)->second;
    out << "==============================\n";
    out << "Dictionary <" << dictName << ">:\n";

    if (nessDict.empty()) {
      out << "is empty.\n";
    }

    for (auto dictStrIt = nessDict.begin(); dictStrIt != nessDict.end(); dictStrIt++) {
      out << "{ " << dictStrIt->first << " - ";
      for (auto translationsIt = dictStrIt->second.begin(); translationsIt != dictStrIt->second.end(); translationsIt++) {
        out << *translationsIt << "; ";
      }
      out << "}" << '\n';
    }
    out << "==============================\n";
  }
  else {
    throw std::logic_error("No such dictionary.");
  }
}

void ananjeva::countWordsInDict(mapOfDictionaries& allDictionaries, std::istream& in, std::ostream& out) {
  std::string dictName = "";
  in >> dictName;
  if (dictName == "") {
    throw std::invalid_argument("No one dictionary was chosen.");
  }
  if (allDictionaries.count(dictName) == 1) {
    std::size_t countWords = 0;
    dictTypeWithoutName nessDict = allDictionaries.find(dictName)->second;
    for (auto it = nessDict.begin(); it != nessDict.end(); it++) {
      ++countWords;
    }
    out << "Dictionary <" << dictName << "> has " << countWords << " words.\n";
  }
  else {
    throw std::logic_error("No such dictionary");
  }
}

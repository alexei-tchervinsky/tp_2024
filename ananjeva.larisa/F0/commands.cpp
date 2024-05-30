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

  DictIO newPair;

  while (!in.eof()) {

    in >> newPair;
    if (in.fail() && !in.eof()) {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    inputDictionary[newPair.dictStr.first] = newPair.dictStr.second;
  }
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

void ananjeva::addDictToDict(mapOfDictionaries& allDictionaries, std::istream& in, std::ostream& out) {
  std::string dictNameWhat = "";
  std::string dictNameWhere = "";
  in >> dictNameWhat;
  in >> dictNameWhere;

  if (dictNameWhat == "" || dictNameWhere == "") {
    throw std::invalid_argument("One of the dictionaries wasn't chosen.");
  }

  auto dictWhatIt = allDictionaries.find(dictNameWhat);
  auto dictWhereIt = allDictionaries.find(dictNameWhere);
  if (dictWhatIt != allDictionaries.end() && dictWhereIt != allDictionaries.end()) {
    for (auto it = dictWhatIt->second.begin(); it != dictWhatIt->second.end(); it++) {
      (dictWhereIt->second).emplace(it->first, it->second);
    }
    out << "Dictionary '" << dictNameWhat << "' was added to dictionary '" << dictNameWhere << "' successfully.\n";
  }
  else {
    out << "One of the dictionaries doesn't exist.\n";
  }
}

void ananjeva::uniteDictionaries(mapOfDictionaries& allDictionaries, std::istream& in, std::ostream& out) {
  std::string newDictName = "";
  std::string firstDictName = "";
  std::string secondDictName = "";
  in >> newDictName >> firstDictName >> secondDictName;

  if (newDictName == "" || firstDictName == "" || secondDictName == "") {
    throw std::invalid_argument("One of the dictionaries wasn't chosen.");
  }

  dictTypeWithoutName newDict {};
  allDictionaries.emplace(newDictName, newDict);

  auto firstDictIt = allDictionaries.find(firstDictName);
  auto secondDictIt = allDictionaries.find(secondDictName);
  auto newDictIt = allDictionaries.find(newDictName);
  if (firstDictIt != allDictionaries.end() && secondDictIt != allDictionaries.end()) {
    for (auto it = firstDictIt->second.begin(); it != firstDictIt->second.end(); it++) {
      (newDictIt->second).emplace(it->first, it->second);
    }
    for (auto it = secondDictIt->second.begin(); it != secondDictIt->second.end(); it++) {
      (newDictIt->second).emplace(it->first, it->second);
    }
    out << "Dictionaries '" << firstDictName << "' and '" << secondDictName << "' were united to dictionary '"
      << newDictName << "' successfully.\n";
  }
  else {
    out << "One of the dictionaries doesn't exist.\n";
  }
}

void ananjeva::removeDict(mapOfDictionaries& allDictionaries, std::istream& in, std::ostream& out) {
  std::string delDictName = "";
  in >> delDictName;
  if (allDictionaries.erase(delDictName)) {
    out << "Dictionary <" << delDictName << "> was deleted.\n";
  }
  else {
    out << "Dictionary <" << delDictName << "> was not deleted.\n";
  }
}

void ananjeva::SelectedDictionary::selectDict(mapOfDictionaries& allDictionaries, std::istream& in, std::ostream& out) {
  std::string selectedDictName = "";
  in >> selectedDictName;
  auto selectedDictIt = allDictionaries.find(selectedDictName);

  if (selectedDictIt == allDictionaries.end()) {
    dictTypeWithoutName dictionary {};
    allDictionaries.emplace(selectedDictName, dictionary);
    selectedDictionaryName_ = selectedDictName;
    out << "New dictionary <" << selectedDictName << "> was created and selected.\n";
  }
  else {
    selectedDictionaryName_ = selectedDictName;
    out << "Dictionary <" << selectedDictName << "> was selected.\n";
  }
}

void ananjeva::SelectedDictionary::insertDict(mapOfDictionaries& allDictionaries, std::istream& in, std::ostream& out) {
  if (selectedDictionaryName_ == "") {
    out << "Try to select a dictionary using 'select < dictionary name >'\n";
    throw std::logic_error("No one dictionary was selected.");
  }
  auto dictionaryIt = allDictionaries.find(selectedDictionaryName_);
  DictIO newPair;
  in >> newPair;
  if (in.fail()) {
    throw std::invalid_argument("Invalid command in insertation.");
  }
  std::string engPart = newPair.dictStr.first;
  std::set< std::string > rusPart = newPair.dictStr.second;
  if (dictionaryIt->second.count(engPart) == 0) {
    (dictionaryIt->second)[engPart] = rusPart;
  }
  else {
    for (auto rusWord = rusPart.cbegin(); rusWord != rusPart.cend(); rusWord++) {
      if (((dictionaryIt->second)[engPart]).find(*rusWord) == ((dictionaryIt->second)[engPart]).end()) {
        ((dictionaryIt->second)[engPart]).insert(*rusWord);
      }
    }
  }

  out << "Insertation in <" << selectedDictionaryName_ << "> is successful\n";
}

void ananjeva::SelectedDictionary::findWordInDict(mapOfDictionaries& allDictionaries, std::istream& in, std::ostream& out) {
  std::string dictName = selectedDictionaryName_;
  if (dictName == "") {
    out << "Try to select a dictionary using 'select < dictionary name >'\n";
    throw std::invalid_argument("No one dictionary was chosen.");
  }
  if (allDictionaries.count(dictName) == 1) {
    std::string enteredWord = "";
    in >> enteredWord;
    dictTypeWithoutName dictionary = allDictionaries.find(selectedDictionaryName_)->second;
    auto dictStrIt = dictionary.find(enteredWord);
    if (dictStrIt != dictionary.end()) {
      out << "The word '" << enteredWord << "' was found:\n";
      out << "{ " << dictStrIt->first << " - ";
      for (auto translationsIt = dictStrIt->second.begin(); translationsIt != dictStrIt->second.end(); translationsIt++) {
        out << *translationsIt << "; ";
      }
      out << "}" << '\n';
    }
    else {
      out << "The word '" << enteredWord << "' wasn't found.\n";
    }
  }
  else {
    throw std::logic_error("No such dictionary");
  }
}

void ananjeva::SelectedDictionary::deleteWordInDict(mapOfDictionaries& allDictionaries, std::istream& in, std::ostream& out) {
  std::string dictName = selectedDictionaryName_;
  if (dictName == "") {
    out << "Try to select a dictionary using 'select < dictionary name >'\n";
    throw std::invalid_argument("No one dictionary was chosen.");
  }
  if (allDictionaries.count(dictName) == 1) {
    auto dictionaryIt = allDictionaries.find(selectedDictionaryName_);
    std::string enteredWord = "";
    in >> enteredWord;

    auto dictStrIt = (dictionaryIt->second).find(enteredWord);
    if (dictStrIt != (dictionaryIt->second).end()) {
      dictionaryIt->second.erase(enteredWord);
      out << "The word '" << enteredWord << "' was deleted successfully.\n";
    }
    else {
      out << "The word '" << enteredWord << "' wasn't found and deleted.\n";
    }
  }
  else {
    throw std::logic_error("No such dictionary");
  }
}

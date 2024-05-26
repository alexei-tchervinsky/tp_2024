#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>

namespace mynspace
{
  using dictionary = std::unordered_map< std::string, std::size_t >;
  using dictionaries = std::map< std::string, dictionary >;

  std::string getText(const char* file);
  std::string toLower(std::string text);
  std::string cleanText(std::string text);

  void getTopOfNumber(dictionary& dict, std::ostream& out, int number);

  void searchWord(dictionary& dict, std::ostream& out, std::istream& in);
  void searchNumber(dictionary& dict, std::ostream& out, std::istream& in);

  void deleteWord(dictionaries& dicts, std::ostream& out, std::istream& in);
  void deleteDictionary(dictionaries& dicts, std::ostream& out, std::istream& in);

  void showAllDictionaries(dictionaries& dicts, std::ostream& out);
  void showAllWords(dictionary& dict, std::ostream& out);
}

#endif
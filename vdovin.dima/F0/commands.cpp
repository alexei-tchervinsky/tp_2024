#include "commands.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>

void vdovin::addDictionary(std::istream& in, std::map<std::string, std::map<std::string, std::vector<std::string>>>& dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) != dictionaries.end())
  {
    throw std::logic_error("<ALREADY EXISTS>");
  }
  std::map<std::string, std::vector<std::string>> new_dict;
  dictionaries[name] = new_dict;
}

void vdovin::deleteDictionary(std::istream& in,
  std::map<std::string, std::map<std::string, std::vector<std::string>>>& dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  dictionaries.erase(name);
}

void vdovin::addWord(std::istream& in,
  std::map<std::string, std::map<std::string, std::vector<std::string>>>& dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  std::map<std::string, std::vector<std::string>>& needed_dict = dictionaries[name];
  std::string word = "";
  std::string translation = "";
  in >> word >> translation;
  needed_dict[word].push_back(translation);
}

void vdovin::removeWord(std::istream& in,
  std::map<std::string, std::map<std::string, std::vector<std::string>>>& dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  std::map<std::string, std::vector<std::string>>& needed_dict = dictionaries[name];
  std::string word = "";
  in >> word;
  if (needed_dict.find(word) == needed_dict.end())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  needed_dict.erase(word);
}

void vdovin::translate(std::ostream& out,
  std::istream& in,
  const std::map<std::string, std::map<std::string, std::vector<std::string>>>& dictionaries)
{
  std::string name = "";
  std::string eng_word = "";
  in >> name >> eng_word;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  const std::map<std::string, std::vector< std::string>>& needed_dict = dictionaries.at(name);

  if (needed_dict.find(eng_word) == needed_dict.end())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  const std::vector<std::string> translations = needed_dict.at(eng_word);
  out << eng_word << " ";
  std::copy(translations.cbegin(), translations.cend(), std::ostream_iterator<std::string>(out, " "));
  out << "\n";
  return;
}

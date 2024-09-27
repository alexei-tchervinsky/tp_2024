#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace vdovin
{
  void addDictionary(std::istream&, std::map<std::string, std::map<std::string, std::vector<std::string>>>&);
  void deleteDictionary(std::istream&, std::map<std::string, std::map<std::string, std::vector<std::string>>>&);
  void addWord(std::istream&, std::map<std::string, std::map<std::string, std::vector<std::string>>>&);
  void removeWord(std::istream&, std::map<std::string, std::map<std::string, std::vector<std::string>>>&);
  void translate(std::ostream&, std::istream&, const std::map<std::string, std::map<std::string, std::vector<std::string>>>&);
}

#endif

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <unordered_map>

namespace semzin
{
  void commands(std::ostream &out);
  void make(std::unordered_map<std::string, std::size_t> &frequencyDict, std::istream &in, std::ostream &out);
  void sortMtoL(std::unordered_map<std::string, std::size_t> &frequencyDict, std::ostream &out);
  void sortLtoM(std::unordered_map<std::string, std::size_t> &frequencyDict, std::ostream &out);
  void print(std::unordered_map<std::string, std::size_t> &frequencyDict, std::ostream &out);
  void holyTrinityMost(std::unordered_map<std::string, std::size_t> &frequencyDict, std::ostream &out);
  void holyTrinityLeast(std::unordered_map<std::string, std::size_t> &frequencyDict, std::ostream &out);
  bool comparatorMax(const std::pair<std::string, std::size_t> &currPair, const std::pair<std::string, std::size_t> &nextPair);
  bool comparatorMin(const std::pair<std::string, std::size_t> &currPair, const std::pair<std::string, std::size_t> &nextPair);
  void findWord(std::unordered_map<std::string, std::size_t> &frequencyDict, std::istream &in, std::ostream &out);
  void removeWord(std::unordered_map<std::string, std::size_t> &frequencyDict, std::istream &in, std::ostream &out);
  void remove(std::unordered_map<std::string, std::size_t> &frequencyDict, std::ostream &out);
  void save(std::unordered_map<std::string, std::size_t> &frequencyDict, std::istream &in, std::ostream &out);
}

#endif

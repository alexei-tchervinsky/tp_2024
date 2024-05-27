#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <unordered_map>

namespace leontiev
{
  void help(std::ostream &out);
  void create(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out);
  void display(std::unordered_map<std::string, std::size_t>& frDict, std::ostream& out);
  void top(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out);
  void findWord(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out);
  void clear(std::unordered_map<std::string, std::size_t>& frDict, std::ostream& out);
  void merge(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out);
  void findN(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out);
  void out(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out);
}


#endif

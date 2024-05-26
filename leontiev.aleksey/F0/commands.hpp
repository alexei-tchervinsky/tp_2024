#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>

namespace leontiev
{
  void help(std::ostream &out);
  void create(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out);
  void display(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out);
  void top(std::unordered_map<std::string, std::size_t>& frDict, std::istream& in, std::ostream& out);
}


#endif
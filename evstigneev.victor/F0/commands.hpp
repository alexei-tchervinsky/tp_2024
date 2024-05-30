#ifndef COMMANDS_HPP
#define COMMAND_HPP
#include <iostream>
#include <unordered_map>

namespace evstigneev
{
  using dictionary = std::unordered_map<std::string, std::size_t>;

  void help(std::ostream& out);
  void create(dictionary& dict, std::istream& in, std::ostream& out);
  void top(dictionary& dict, std::istream& in, std::ostream& out);
  void find(dictionary& dict, std::istream& in, std::ostream& out);
  void merge(dictionary& dict, std::istream& in, std::ostream& out);
  void remove(dictionary& dict, std::ostream& out);
}

#endif

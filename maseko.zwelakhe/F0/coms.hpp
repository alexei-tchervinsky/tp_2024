#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <exception>
#include <iostream>
#include <unordered_map>
#include <map>
#include <fstream>
#include <limits>
#include <utility>
#include <vector>
#include <functional>
#include <sstream>

#include "actions.hpp"

namespace mynspace
{
  using dictionary = std::unordered_map< std::string, std::size_t >;
  using dictionaries = std::map< std::string, dictionary >;

  void getHelp(std::ostream& out, std::istream& in);
  void create(dictionaries& dicts, std::ostream& out, std::istream& in);
  void showDictionary(dictionaries& dicts, std::ostream& out, std::istream& in);
  void showTop(dictionaries& dicts, std::ostream& out, std::istream& in);
  void search(dictionaries& dicts, std::ostream& out, std::istream& in);
  void deleteDict(dictionaries& dicts, std::ostream& out, std::istream& in);
  void getIntersections(dictionaries& dicts, std::ostream& out, std::istream& in);
  void merge(dictionaries& dicts, std::ostream& out, std::istream& in);
  void getAll(dictionaries& dicts, std::ostream& out, std::istream& in);
  void save(dictionaries& dicts, std::ostream& out, std::istream& in);
  void sort(dictionaries& dicts, std::ostream& out, std::istream& in);
}

#endif
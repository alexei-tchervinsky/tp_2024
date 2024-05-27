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

#include "functions.hpp"

namespace gredasov
{
  using dictionary = std::unordered_map< std::string, std::size_t >;
  using dictionaries = std::map< std::string, dictionary >;

  void getHelpCommand(std::ostream& out, std::istream& in);
  void createCommand(dictionaries& dicts, std::ostream& out, std::istream& in);
  void showDictionaryCommand(dictionaries& dicts, std::ostream& out, std::istream& in);
  void showTopCommand(dictionaries& dicts, std::ostream& out, std::istream& in);
  void searchCommand(dictionaries& dicts, std::ostream& out, std::istream& in);
  void deleteCommand(dictionaries& dicts, std::ostream& out, std::istream& in);
  void getIntersectionsCommand(dictionaries& dicts, std::ostream& out, std::istream& in);
  void mergeCommand(dictionaries& dicts, std::ostream& out, std::istream& in);
  void getAllCommand(dictionaries& dicts, std::ostream& out, std::istream& in);
  void saveCommand(dictionaries& dicts, std::ostream& out, std::istream& in);
  void sortCommand(dictionaries& dicts, std::ostream& out, std::istream& in);
}

#endif


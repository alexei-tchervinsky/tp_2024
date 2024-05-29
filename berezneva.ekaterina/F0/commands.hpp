#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "io.hpp"
#include <map>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <limits>
#include <exception>

using untitledDict = std::map< std::string, std::set< std::string > >;
using DictMap = std::map< std::string, std::map< std::string, std::set< std::string > > >;

namespace berezneva {
  untitledDict input(std::istream& in);
  void info(std::ostream& out);
  void create(DictMap& Dicts, std::istream& in, std::ostream& out);
  void remove(DictMap& Dicts, std::istream& in, std::ostream& out);
  void search(DictMap& Dicts, std::istream& in, std::ostream& out);
  void rename(DictMap& Dicts, std::istream& in, std::ostream& out);
  void allDictNames(DictMap& Dicts, std::ostream& out);
  void countWords(DictMap& Dicts, std::istream& in, std::ostream& out);
}

#endif

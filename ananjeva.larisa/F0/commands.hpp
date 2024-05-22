#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "dataStruct.hpp"
#include <map>

using dictTypeWithoutName = std::map< std::string, std::set< std::string > >;
using dictType = std::pair< std::string, std::map< std::string, std::set< std::string > > >;
using mapOfDictionaries = std::map< std::string, std::map< std::string, std::set< std::string > > >;

namespace ananjeva {
  void printCommands(std::ostream& out);
  dictTypeWithoutName getDictFromInput(std::istream& in);
  void createDict(mapOfDictionaries&, std::istream&, std::ostream&);
  void renameDict(mapOfDictionaries&, std::istream&, std::ostream&);
}

#endif

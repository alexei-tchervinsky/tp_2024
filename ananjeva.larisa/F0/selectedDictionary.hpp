#ifndef SELECTED_DICTIONARY_HPP
#define SELECTED_DICTIONARY_HPP

#include <string>
#include <map>
#include <set>

using dictTypeWithoutName = std::map< std::string, std::set< std::string > >;
using dictType = std::pair< std::string, std::map< std::string, std::set< std::string > > >;
using mapOfDictionaries = std::map< std::string, std::map< std::string, std::set< std::string > > >;

namespace ananjeva {
  class SelectedDictionary {
  public:
    void selectDict(mapOfDictionaries&, std::istream&, std::ostream&);
    void insertDict(mapOfDictionaries&, std::istream&, std::ostream&);
    void deleteWordInDict(mapOfDictionaries&, std::istream&, std::ostream&);
    void findWordInDict(mapOfDictionaries&, std::istream&, std::ostream&);

  private:
    std::string selectedDictionaryName_ = "";
  };
}

#endif

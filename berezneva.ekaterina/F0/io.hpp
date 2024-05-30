#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <string>
#include <set>

namespace berezneva
{

  struct En
  {
    std::string& en_;
  };

  struct Rus
  {
    std::set< std::string >& rus_;
  };

  struct Dict
  {
    // <en_word> <rus_value 1><rus_value 2>...<rus_value N>
    std::pair< std::string, std::set< std::string > > str_;
  };

  struct Delimiter
  {
    const char expected_;
  };

  std::istream& operator>>(std::istream& in, Rus&& dest);
  std::istream& operator>>(std::istream& in, En&& dest);
  std::istream& operator>>(std::istream& in, Dict& dest);
  std::istream& operator>>(std::istream& in, Delimiter&& dest);
}

#endif

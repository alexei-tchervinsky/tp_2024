#ifndef STRUCT_HPP
#define STRUCT_HPP
#include <iostream>
#include <string>

namespace ananev
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char del;
  };

  struct LITIO
  {
    unsigned long long &lit;
  };

  struct HEXIO
  {
    unsigned long long &hex;
  };

  struct StringIO
  {
    std::string &str;
  };

  struct LabelIO
  {
    std::string lab;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, LITIO &&dest);
  std::istream &operator>>(std::istream &in, HEXIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
}

#endif

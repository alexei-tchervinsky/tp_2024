#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>

// ULL LIT | ULL BIN
namespace semzin
{
  struct Data
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

  struct BINIO
  {
    unsigned long long &bin;
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
  std::istream &operator>>(std::istream &in, BINIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::istream &operator>>(std::istream &in, Data &dest);
  std::ostream &operator<<(std::ostream &out, const Data &dest);
  std::string toBin(unsigned long long key);
}
#endif

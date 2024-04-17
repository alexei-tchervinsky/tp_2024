#ifndef ITERATOR
#define ITERATOR
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>

namespace lst
{
  bool isOct(unsigned long long x);
  struct Data
  {
    unsigned long long key1;
    char key2;
    std::string key3;
  };
  struct DelimiterIO
  {
    char exp;
  };
  struct ULLIO
  {
    unsigned long long &ref;
  };
  struct CharIO
  {
    char &ref;
  };
  struct StringIO
  {
    std::string &ref;
  };
  struct LabelIO
  {
    std::string &exp;
  };
  class iofmtguard;
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, ULLIO &&dest);
  std::istream &operator>>(std::istream &in, CharIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::istream &operator>>(std::istream &in, Data &dest);
  std::ostream &operator<<(std::ostream &out, const Data &dest);
  std::ostream &operator<<(std::ostream &out, const Data &src);
}
#endif

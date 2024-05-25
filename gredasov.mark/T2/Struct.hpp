#ifndef STRUCT_HPP
#define STRUCT_HPP
#include <iostream>
#include <string>

namespace gredasov
{
  struct DoubleIO
  {
    double &ref;
  };

  struct LongLongIO
  {
    long long &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  std::istream &operator>>(std::istream & in, DoubleIO && dest);
  std::istream &operator>>(std::istream & in, LongLongIO && dest);
  std::istream &operator>>(std::istream & in, StringIO && dest);
}

#endif


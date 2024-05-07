#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <iomanip>
#include "Delimiter.hpp"

namespace gredasov
{
  struct DataStruct
  {
    double key1;
    long long key2;
    std::string key3;
  };
  std::istream &operator>>(std::istream & in, DataStruct & dest);
  std::ostream &operator<<(std::ostream & out, const DataStruct & dest);
  bool operator<(const DataStruct& toCompare, const DataStruct& otherToCompare);
}

#endif


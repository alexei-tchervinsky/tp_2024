#ifndef DATASTRUST_HPP
#define DATASTRUCT_HPP
#include <string>
#include <utility>
#include <iostream>
#include "ScopeGuard.hpp"
#include "IOstructures.hpp"
namespace lelkov
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };
  std::istream & operator>>(std::istream &in, DataStruct &value);
  std::ostream & operator<<(std::ostream & out, const DataStruct &value);
  bool operator>(const DataStruct &left, const DataStruct &rigth);
  bool operator<(const DataStruct &left, const DataStruct &rigth);
}

#endif

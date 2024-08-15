#ifndef _DATA_STRUCT_HPP_
#define _DATA_STRUCT_HPP_

#include <iostream>
#include <string>
#include <complex>
#include <utility>

namespace tchervinsky
{
  struct Delimiter
  {
    char delimiter;
  };

  struct Complex
  {
    std::complex<double> &value;
  };

  struct Pair
  {
    std::pair<long long, unsigned long long> &val;
  };
  struct String
  {
    std::string &str;
  };

#if 0
  struct LongLong
  {
    long long &value;
  };
#endif
  struct DataStruct
  {
    std::complex<double> key1;
#if 0
    long long key1;
#endif
    std::pair<long long, unsigned long long> key2;
    std::string key3;
  };

  std::istream& operator >> (std::istream& in, Delimiter&& dest);
#if 0
  std::istream& operator >> (std::istream& in, LongLong&& dest);
#endif
  std::istream& operator >> (std::istream& in, Complex&& dest);
  std::istream& operator >> (std::istream& in, Pair&& dest);
  std::istream& operator >> (std::istream& in, String&& dest);
  std::istream& operator >> (std::istream& in, DataStruct& dest);
  std::ostream& operator << (std::ostream& out, const DataStruct& dest);
  bool operator < (const DataStruct& a, const DataStruct& b);
}
#endif

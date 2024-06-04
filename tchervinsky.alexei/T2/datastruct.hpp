#ifndef _DATA_STRUCT_HPP_
#define _DATA_STRUCT_HPP_

#include <iostream>
#include <string>
#include <ccomplex>

namespace tchervinsky
{
  struct DelimiterIO
  {
    char delimiter;
  };

  struct LongLongIO
  {
    long long &ll;
  };

  struct DataStruct
  {
    long long key1;
    std::complex<double> key2;
    std::string key3;
  };

  std::istream& operator >> (std::istream& in, DelimiterIO&& dest);
  std::istream& operator >> (std::istream& in, LongLongIO&& dest);
  std::istream& operator >> (std::istream& in, DataStruct& dest);
  std::ostream& operator << (std::ostream& out, const DataStruct& dest);
  bool operator < (const DataStruct& a, const DataStruct& b);

  // scope guard для возврата состояния потока в первоначальное состояние
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char > &s);
    ~iofmtguard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}
#endif

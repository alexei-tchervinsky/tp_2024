#ifndef _DATA_STRUCT_HPP_
#define _DATA_STRUCT_HPP_
#include <iostream>
#include <string>

namespace bekhova
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

  struct ULLOctIO
  {
  h  unsigned long long& ull;
  };
  struct ULLHexIO
  {
    unsigned long long& ref;
  };
  struct DelimiterIO
  {
    char delimiter;
  };

  struct StringIO
  {
    std::string& str;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& d);
  std::istream& operator>>(std::istream& in, ULLOctIO&& d);
  std::istream& operator>>(std::istream& in, ULLHexIO&& d);
  std::istream& operator>>(std::istream& in, StringIO&& d);
  std::istream& operator>>(std::istream& in, DataStruct& d);
  std::ostream& operator<<(std::ostream& out, const DataStruct& d);
  bool operator<(const DataStruct& a, const DataStruct& b);

  class iofmtguard
  {
  public:
    explicit iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}
#endif
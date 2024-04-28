#ifndef _DATA_STRUCT_HPP_
#define _DATA_STRUCT_HPP_
#include <iostream>
#include <string>

namespace evstigneev
{
  struct DataStruct
  {
    unsigned long long key1;
    char key2;
    std::string key3;
  };

  struct ULLOctIO
  {
    unsigned long long& ull;
  };

  struct DelimiterIO
  {
    char delimiter;
  };

  struct StringIO
  {
    std::string& str;
  };

  struct CharLitIO
  {
    char& chr;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, ULLOctIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, CharLitIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
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

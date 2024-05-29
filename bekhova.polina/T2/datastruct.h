#ifndef _DATASTRUCT_H
#define _DATASTRUCT_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <regex>

namespace bekhova
{
  bool is_ULL_OCT(const std::string& str);
  bool is_ULL_HEX(const std::string& str);
  bool isString(const std::string& str);

  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& ds);
  std::ostream& operator<<(std::ostream& out, const DataStruct& ds);

  std::pair<std::string, std::string> getNextPair(std::string& s);

  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}
#endif

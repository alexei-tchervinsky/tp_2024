#ifndef MYNSPACE_HPP
#defind MYNSPACE_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>

namespace nspace
{
  // формат ввода:
  // { "key1": 1.0d, "key2": "Let madness release you" }
  struct Data
  {
    double key1;
    long long key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleIO
  {
    double &ref;
  };
  
  struct LongLIO
  {
    long long &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  struct LabelIO
  {
    std::string exp;
  };

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

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, DoubleIO &&dest);
  std::istream &operator>>(std::istream &in, LongLIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::istream &operator>>(std::istream &in, Data &dest);
  std::ostream &operator<<(std::ostream &out, const Data &dest);
  
  void sort(std::vector< nspace::Data > Items[], size_t size);
  bool sorted(std::vector< nspace::Data > Items[], size_t size);
}

#endif

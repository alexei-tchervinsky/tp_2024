#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <cmath>
#include <iostream>
#include <sstream>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>

#include "WrongInput.h"

namespace grudov
{
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
  struct LITIO
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

  std::string makeDoubleScientific(double val);

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, DoubleIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::istream &operator>>(std::istream &in, Data &dest);
  std::istream &operator>>(std::istream &in, LITIO &&dest);
  std::ostream &operator<<(std::ostream &out, const Data &dest);
}
#endif
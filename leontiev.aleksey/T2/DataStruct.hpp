#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <iomanip>
#include <string>

namespace leontiev
{
  struct DataStruct
  {
    double key1;
    char key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct CharIO
  {
    char &ref;
  };

  struct DoubleIO
  {
    double &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  struct LabelIO
  {
    std::string exp;
  };
  std::istream &operator>>(std::istream & in, DelimiterIO && dest);
  std::istream &operator>>(std::istream & in, DoubleIO && dest);
  std::istream &operator>>(std::istream & in, CharIO && dest);
  std::istream &operator>>(std::istream & in, StringIO && dest);
  std::istream &operator>>(std::istream & in, DataStruct & dest);
  std::ostream &operator<<(std::ostream & out, const DataStruct & dest);
  bool operator<(const DataStruct& firstOperand, const DataStruct& secondOperand);
}

#endif

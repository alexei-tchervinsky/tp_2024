#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
// DBL SCI SLL LIT
#include <string>
namespace kabalin {
struct DataStruct {
  double key1;
  long long key2;
  std::string key3;
};

struct DelimiterIO {
  char exp;
};

struct DoubleIO {
  double &ref;
};
struct LITIO {
  long long &ref;
};

struct StringIO {
  std::string &ref;
};

struct LabelIO {
  std::string exp;
};
std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
std::istream &operator>>(std::istream &in, DoubleIO &&dest);
std::istream &operator>>(std::istream &in, StringIO &&dest);
std::istream &operator>>(std::istream &in, LabelIO &&dest);
std::istream &operator>>(std::istream &in, DataStruct &dest);
std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
} // namespace kabalin

#endif
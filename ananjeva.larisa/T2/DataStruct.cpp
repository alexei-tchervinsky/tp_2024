#include "DataStruct.hpp"
#include"delimiter.hpp"
#include"structures.hpp"
#include"scopeGuard.hpp"
#include<iomanip>

std::istream& ananjeva::operator>>(std::istream& in, DataStruct& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  DataStruct inputStruct;
  {
    using del = DelimiterIO;
    using dbl = DoubleIO;
    using chr = CharIO;
    using str = StringIO;
    std::string key = "";
    in >> del{ '(' };
    for (std::size_t i = 0; i < 3; i++) {
      in >> del{ ':' } >> key;
      if (key == "key1") {
        in >> dbl{ inputStruct.key1 };
      }
      else if (key == "key2") {
        in >> chr{ inputStruct.key2 };
      }
      else if (key == "key3") {
        in >> str{ inputStruct.key3 };
      }
      else {
        in.setstate(std::ios::failbit);
      }
    }
    in >> del{ ':' } >> del{ ')' };
  }
  if (in) {
    dest = inputStruct;
  }
  return in;
}

std::ostream& ananjeva::operator<<(std::ostream& out, const DataStruct& src) {
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }

  iofmtguard fmtguard(out);
  out << "(:key1 ";
  outputDoubleScience(out, src.key1);
  out << ":key2 " << "'" << src.key2 << "'" << ":key3 " << '"' << src.key3 <<
    '"' << ":)";
  return out;
}

bool ananjeva::operator<(const DataStruct& lhs, const DataStruct& rhs) {
  if (lhs.key1 == rhs.key1) {
    if (lhs.key2 == rhs.key2) {
      return (lhs.key3.size() < rhs.key3.size());
    }
    else {
      return lhs.key2 < rhs.key2;
    }
  }
  else {
    return lhs.key1 < rhs.key1;
  }
}

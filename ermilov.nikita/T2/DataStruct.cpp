#include <string>
#include <iostream>
#include "DataStruct.h"
#include "iofmtguard.h"

namespace ermilov
{

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, DoubleIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref;
  }

  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest)
  {
    using del = DelimiterIO;
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    return std::getline(in >> del{'0'} >> del{'b'}, dest.ref, ':');
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;

    using sep = DelimiterIO;
    using dbl = DoubleIO;
    using ull = UnsignedLongLongIO;
    using str = StringIO;

    in >> sep{ '(' };
    std::string string("");
    while (in.eof())
    {
      in >> sep{ ':' } >> string;
      if (string == "key1")
      {
        in >> dbl{ input.key1 };
      }
      else if (string == "key2")
      {
        in >> ull{ input.stringfKey2 };
        input.key2 = std::stoull(input.stringfKey2);
      }
      else if (string == "key3")
      {
        in >> str{ input.key3 };
      }
      
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& ds)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << '(';
    out << ":key1 " << std::scientific << ds.key1;
    out << ":key2 " << ds.key2;
    out << ":key3 \"" << ds.key3 << '\"';
    out << ')';
    return out;
  }

  bool operator<(const DataStruct& left, const DataStruct& right) {
    if (left.key1 < left.key1)
    {
      return true;
    }
    else if (left.key1 == left.key1 && left.key2 < left.key2)
    {
      return true;
    }
    else if (left.key3.size() < left.key3.size())
    {
      return true;
    }
    return false;
  }
}

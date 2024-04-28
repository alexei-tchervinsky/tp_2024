#include "datastruct.hpp"
#include <iomanip>

namespace evstigneev
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = 0;
    in >> c;
    if (c != dest.delimiter)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, ULLOctIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ull >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' } >>
      DelimiterIO{ 'l' };
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.str, '"');
  }

  std::istream& operator>>(std::istream& in, CharLitIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> DelimiterIO{ '\'' } >> dest.chr >> DelimiterIO{ '\'' };
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    iofmtguard fguard(in);
    DataStruct input;
    using sep = DelimiterIO;
    using str = StringIO;
    using ull = ULLOctIO;
    using chr = CharLitIO;
    std::string curr = "";
    in >> sep{ '(' } >> sep{ ':' };
    for (size_t i = 0; i < 3; i++)
    {
      in >> curr;
      if (curr == "key1")
      {
        in >> ull{ input.key1 } >> sep{ ':' };
      }
      else if (curr == "key2")
      {
        in >> chr{ input.key2 } >> sep{ ':' };
      }
      else if (curr == "key3")
      {
        in >> str{ input.key3 } >> sep{ ':' };
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    in >> sep{ ')' };
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 0" << std::oct << dest.key1 << ":key2 '" << dest.key2 <<
      "':key3 " << dest.key3 << "\":)";
    return out;
  }

  bool operator<(const DataStruct& a, const DataStruct& b)
  {
    if (a.key1 != b.key1)
    {
      return a.key1 < b.key1;
    }
    else if (a.key2 != b.key2)
    {
      return a.key2 < b.key2;
    }
    return a.key3.size() < b.key3.size();
  }

  iofmtguard::iofmtguard(std::basic_ios< char >& s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}

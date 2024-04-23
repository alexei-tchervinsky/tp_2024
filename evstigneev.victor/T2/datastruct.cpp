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
    char c = '\0';
    in >> c;
    if (in && (c != dest.delimiter))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, ULLOctIO&& dest)
  {
    using sep = evstigneev::DelimiterIO;
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> sep{ '0' } >> std::oct >> dest.ull;
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
    char c;
    in >> c;
    if (c == '\n')
    {
      in >> dest.chr;
      in.ignore(1);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string d = "";
    in >> d;
    if ((in >> StringIO{ d }) && (d != dest.str))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
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
    in >> sep{ '(' };
    for (size_t i = 0; i < 3; i++)
    {
      in >> sep{ ':' } >> str{ curr };
      if (curr == "key1")
      {
        in >> ull{ input.key1 };
      }
      else if (curr == "key2")
      {
        in >> chr{ input.key2 };
      }
      else if (curr == "key3")
      {
        in >> str{ input.key3 };
      }
    }
    in >> sep{ ':' } >> sep{ ')' };
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
      "':key3 \"" << dest.key3 << "\":)";
    return out;
  }

  bool operator<(const DataStruct& a, const DataStruct& b)
  {
    return (a.key1 < b.key1 || a.key2 < b.key2 || a.key3.size() < b.key3.size());
  }

  iofmtguard::iofmtguard(std::basic_ios<char>& s) :
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

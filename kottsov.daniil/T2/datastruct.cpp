#include "datastruct.h"
#include <limits>

namespace lst
{
  BadInput::BadInput()
  {
    reason_ = "bad input line";
  }
  BadInput::BadInput(const char* reason)
  {
    reason_ = reason;
  }
  const char* BadInput::what() const noexcept
  {
    return reason_;
  }
  constexpr auto max_buffer = std::numeric_limits<std::streamsize>::max();
  bool isOct(unsigned long long x) {
    while(x!=0)
    {
      if (x%10>7) {
        return false;
      }
     x=x/10;
    }
    return true;
  }
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
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
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
  std::istream &operator>>(std::istream &in, ULLIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
      return in >> DelimiterIO{'0'}>> dest.ref;
  }
  std::istream &operator>>(std::istream &in, CharIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> DelimiterIO{'\''} >> dest.ref >> DelimiterIO{'\''};
  }
  std::istream &operator>>(std::istream& in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '\"' }, dest.ref, '\"');
  }
  std::istream &operator>>(std::istream& in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.exp;
  }
  std::istream &operator>>(std::istream &in, Data &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string current;
    Data input;
    {
      using sep = DelimiterIO;
      using str = StringIO;
      using ull = ULLIO;
      using chr = CharIO;
      using label = LabelIO;
      in >> sep{ '(' };
      for (size_t i = 0; i<3; i++)
      {
        in >> sep{ ':' };
        in >> label{ current };
        if (current == "key1" )
        {
          in >> ull{ input.key1 };
          if (!in)
          {
            throw BadInput("key1");
          }
          if (!isOct(input.key1)) {
            throw BadInput("Key1");
          }
        }
        else if (current == "key2")
        {
          in >> chr{ input.key2 };
          if (!in)
          {
            throw BadInput("key2");
          }
        }
        else if (current == "key3")
        {
          in >> str{ input.key3 };
          if (!in)
          {
            throw BadInput("key3");
          }
        }
        else
        {
          throw BadInput("key null");
        };
      }
      in >> sep{ ':' } >> sep{ ')' };
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }
  std::ostream &operator<<(std::ostream &out, const Data &src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(";
    out << ":key1 " << "0" << src.key1 << "";
    out << ":key2 " << '\'' << src.key2 << '\'';
    out << ":key3 " << '\"' << src.key3 << '\"';
    out << ":)";
    return out;
  }
  iofmtguard::iofmtguard(std::basic_ios< char > &s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {};
  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}

#include "Struct.hpp"
#include "Guard.hpp"

namespace ananev
{
  bool isHex(unsigned long long hex)
  {
    while(hex != 0)
    {
      if ((hex%10 < '0' || hex%10 > '9') && (hex%10 < 'A' || hex%10 > 'F'))
      {
        return false;
      }
    }
    return true;
  }

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.del))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, LITIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> dest.lit;
    if (in.peek() == 'U')
    {
      return in >> DelimiterIO{ 'U' } >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
    }
    else
    {
      return in >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
    }
  }

  std::istream &operator>>(std::istream &in, HEXIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> DelimiterIO{ '0' };
    if (in.peek() == 'x')
    {
      return in >> DelimiterIO{ 'x' } >> dest.hex;
    }
    else
    {
      return in >> DelimiterIO{ 'X' } >> dest.hex;
    }
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.str, '"');
  }

  std::istream &operator>>(std::istream &in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.lab))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, DataStruct &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    std::string characters;
    {
      using sep = DelimiterIO;
      using label = LabelIO;
      using lit = LITIO;
      using hex = HEXIO;
      using str = StringIO;
      in >> sep{ '(' };
      for(std::size_t i = 1; i <= 3; i++)
      {
        in >> sep{ ':' };
        in >> label{ characters };
        if (characters == "key1")
        {
          in >> lit{ input.key1 };
        }
        else if (characters == "key2")
        {
          in >> hex{ input.key2 };
        }
        else
        {
          in >> str{ input.key3 };
        }
      }
      in >> sep{ ':' };
      in >> sep{ ')' };
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const DataStruct &src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    Guard fmtguard(out);
    out << "(:key1 " << src.key1 << "ull";
    out << ":key2 0x" << src.key2;
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
  }
}

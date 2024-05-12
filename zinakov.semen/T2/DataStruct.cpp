#include "DataStruct.hpp"
#include "iofmtguard.hpp"

namespace semzin
{
  std::string toBin(unsigned long long key)
  {
    unsigned long long key_ = key;
    std::string bin = "";
    if (key_ == 0)
    {
      bin = "0";
    }
    while (key_ != 0)
    {
      bin = std::to_string(key_ % 2) + bin;
      key_ = key_ / 2;
    }
    return bin;
  }

  unsigned long long BinToDec(unsigned long long bin)
  {
    unsigned long long result = 0;
    for (unsigned long long i = 1; bin; bin /= 10, i *= 2)
    {
      result += i * (bin % 10);
    }
    return result;
  }

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '\0';
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
    in >> std::dec >> dest.lit;
    if (in.peek() == 'U')
    {
      return in >> DelimiterIO{'U'} >> DelimiterIO{'L'} >> DelimiterIO{'L'};
    }
    else
    {
      return in >> DelimiterIO{'u'} >> DelimiterIO{'l'} >> DelimiterIO{'l'};
    }
  }

  std::istream &operator>>(std::istream &in, BINIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> DelimiterIO{'0'};
    if (in.peek() == 'B')
    {
      in >> DelimiterIO{'B'};
    }
    else
    {
      in >> DelimiterIO{'b'};
    }
    unsigned long long bin = 0;
    in >> bin;
    dest.bin = BinToDec(bin);
    return in;
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.str, '"');
  }

  std::istream &operator>>(std::istream &in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{data}) && (data != dest.lab))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, Data &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Data input;
    std::string chars;

    in >> DelimiterIO{'('};
    for (std::size_t i = 0; i < 3; ++i)
    {
      in >> DelimiterIO{':'};
      in >> chars;
      if (chars == "key1")
      {
        in >> LITIO{input.key1};
      }
      else if (chars == "key2")
      {
        in >> BINIO{input.key2};
      }
      else
      {
        in >> StringIO{input.key3};
      }
    }
    in >> DelimiterIO{':'};
    in >> DelimiterIO{')'};
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
    out << "(:key1 " << src.key1 << "ull";
    out << ":key2 0b" << toBin(src.key2);
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
  }
}

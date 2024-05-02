#include "Struct.hpp"
#include "Guard.hpp"

namespace ananev
{
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
    return in >> dest.lit >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
  }

  std::istream &operator>>(std::istream &in, HEXIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> DelimiterIO{ '0' } >> DelimiterIO{ 'x' } >> dest.hex;
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
    {
      using sep = DelimiterIO;
      using label = LabelIO;
      using lit = LITIO;
      using hex = HEXIO;
      using str = StringIO;
      in >> sep{ '(' };
      in >> sep{ ':' } >> label{ "key1" } >> sep{ ' ' } >> lit{ input.key1 };
      in >> sep{ ':' } >> label{ "key2" } >> sep{ ' ' } >> hex{ input.key2 };
      in >> sep{ ':' } >> label{ "key3" } >> sep{ ' ' } >> str{ input.key3 };
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
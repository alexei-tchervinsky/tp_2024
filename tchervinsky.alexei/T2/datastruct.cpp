#include "datastruct.hpp"
#include <iomanip>

std::istream& tchervinsky::operator>>(std::istream& in, tchervinsky::DelimiterIO&& dest)
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

std::istream& tchervinsky::operator >> (std::istream& in, tchervinsky::LongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  long long ll = 0.0;
  in >> std::skipws >> ll >> std::noskipws
    >> tchervinsky::DelimiterIO{ 'l' }
    >> tchervinsky::DelimiterIO{ 'l' }
    >> tchervinsky::DelimiterIO{ ':' };
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  else
  {
    dest.ll = ll;
  }
  return in;
}

std::istream& tchervinsky::operator >> (std::istream& in, tchervinsky::DataStruct& dest)
{
  char c{ '\0' };
  in >> std::skipws >> tchervinsky::DelimiterIO{ '(' } >> std::noskipws;
  if (!in)
  {
    return in;
  }
  in >> std::noskipws >> tchervinsky::DelimiterIO{ ':' } >> std::noskipws;
  if (!in)
  {
    return in;
  }
  bool keyfields[3]{ false };
  for (std::size_t i = 0; i < 3; ++i)
  {
    std::string key;
    in >> key;
    if (key.size() != 4)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    if (key.substr(0, 3) != "key")
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    c = key[3];
    switch (c)
    {
      case '1':
      {
        in >> tchervinsky::LongLongIO{ dest.key1 };
        if (!in)
        {
          return in;
        }
        keyfields[0] = true;
        break;
      }
      case '2':
      {
        in >> std::skipws >> tchervinsky::DelimiterIO{ '#' };
        if (!in)
        {
          return in;
        }
        in >> std::noskipws >> tchervinsky::DelimiterIO{ 'c' };
        if (!in)
        {
          return in;
        }
        in >> std::noskipws >> tchervinsky::DelimiterIO{ '(' };
        if (!in)
        {
          return in;
        }
        double realvalue;
        in >> std::noskipws >> realvalue;
        if (!in)
        {
          in.setstate(std::ios::failbit);
          return in;
        }
        dest.key2.real(realvalue);
        double imagvalue;
        in >> std::skipws >> imagvalue;
        if (!in)
        {
          in.setstate(std::ios::failbit);
          return in;
        }
        dest.key2.imag(imagvalue);
        in >> std::noskipws >> tchervinsky::DelimiterIO{ ')' };
        if (!in)
        {
          return in;
        }
        in >> std::noskipws >> tchervinsky::DelimiterIO{ ':' };
        if (!in)
        {
          return in;
        }
        keyfields[1] = true;
        break;
      }
      case '3':
      {
        std::string key3string;
        std::getline(in, key3string, '"');
        std::getline(in, key3string, '"');
        if (!in)
        {
          in.setstate(std::ios::failbit);
          return in;
        }
        dest.key3 = key3string;
        keyfields[2] = true;
        in >> std::noskipws >> c >> std::noskipws;
        break;
      }
      default:
      {
        in.setstate(std::ios::failbit);
        return in;
      }
    }
  }
  if (((keyfields[0] == keyfields[1]) == keyfields[2]) == true)
  {
    in >> std::noskipws >> tchervinsky::DelimiterIO{ ')' } >> std::noskipws;
    if (!in)
    {
      return in;
    }
  }
  else
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}

std::ostream& tchervinsky::operator << (std::ostream& out, const tchervinsky::DataStruct& src)
{
  iofmtguard fmtguard(out);
  out << "(";
  out << ":key1 " << src.key1 << 'l' << 'l';
  out << ":key2 " << "#c(" << std::fixed << std::setprecision(1) << src.key2.real() << " " << src.key2.imag() << ')';
  out << ":key3 " << '\"' << src.key3 << '\"';
  out << ":)";
  return out;
}

bool tchervinsky::operator < (const tchervinsky::DataStruct& a, const tchervinsky::DataStruct& b)
{
  if (a.key1 != b.key1)
  {
    return a.key1 < b.key1;
  }
  else if (a.key2 != b.key2)
  {
    double akey2mod = std::fabs(std::sqrt(std::pow(a.key2.real(), 2) + std::pow(a.key2.imag(), 2)));
    double bkey2mod = std::fabs(std::sqrt(std::pow(b.key2.real(), 2) + std::pow(b.key2.imag(), 2)));
    return akey2mod < bkey2mod;
  }
  else
  {
    return a.key3.size() < b.key3.size();
  }
}

tchervinsky::iofmtguard::iofmtguard(std::basic_ios< char > &s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}

tchervinsky::iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}

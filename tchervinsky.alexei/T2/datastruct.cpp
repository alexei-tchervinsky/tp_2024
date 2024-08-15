#include "datastruct.hpp"
#include "stream_guard.hpp"
#include <iomanip>
#include <limits>


std::istream& tchervinsky::operator>>(std::istream& in, tchervinsky::Delimiter&& dest)
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
#if 0
std::istream& tchervinsky::operator >> (std::istream& in, LongLong&& dest)
{
  in >> std::skipws >> dest.value >> std::noskipws
    >> tchervinsky::Delimiter{ 'l' } >> tchervinsky::Delimiter{ 'l' }
    >> tchervinsky::Delimiter{ ':' };
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
#endif

std::istream& tchervinsky::operator >> (std::istream& in, tchervinsky::Complex&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> std::skipws >> tchervinsky::Delimiter{ '#' };
  if (!in)
  {
    return in;
  }
  in >> std::noskipws >> tchervinsky::Delimiter{ 'c' };
  if (!in)
  {
    return in;
  }
  in >> std::noskipws >> tchervinsky::Delimiter{ '(' };
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
  dest.value.real(realvalue);
  double imagvalue;
  in >> std::skipws >> imagvalue;
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest.value.imag(imagvalue);
  in >> std::noskipws >> tchervinsky::Delimiter{ ')' };
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  in >> std::noskipws >> tchervinsky::Delimiter{ ':' };
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}

std::istream& tchervinsky::operator >> (std::istream& in, Pair&& dest)
{
// key2 (:N -1:D 5:):
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> std::skipws >> tchervinsky::Delimiter{ '(' };
  if (!in)
  {
    return in;
  }
  in >> std::noskipws >> tchervinsky::Delimiter{ ':' };
  if (!in)
  {
    return in;
  }
  in >> std::noskipws >> tchervinsky::Delimiter{ 'N' };
  if (!in)
  {
    return in;
  }
  long long first;
  in >> std::skipws >> first;
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  in >> std::noskipws >> tchervinsky::Delimiter{ ':' };
  if (!in)
  {
    return in;
  }
  in >> std::noskipws >> tchervinsky::Delimiter{ 'D' };
  if (!in)
  {
    return in;
  }
  unsigned long long second;
  in >> std::skipws >> second;
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest.val.first = first;
  dest.val.second = second;
  in >> std::noskipws >> tchervinsky::Delimiter{ ':' };
  if (!in)
  {
    return in;
  }
  in >> std::skipws >> tchervinsky::Delimiter{ ')' };
  if (!in)
  {
    return in;
  }
   in >> std::noskipws >> tchervinsky::Delimiter{ ':' };
  if (!in)
  {
    return in;
  }
  return in;
}



std::istream& tchervinsky::operator >> (std::istream& in, String&& dest)
{
  std::string key3string;
  std::getline(in, key3string, '"');
  std::getline(in, key3string, '"');
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest.str = key3string;
  in >> std::skipws >> tchervinsky::Delimiter{ ':' };
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}


std::istream& tchervinsky::operator >> (std::istream& in, tchervinsky::DataStruct& dest)
{
#if 0
  using LongLongIO = tchervinsky::LongLong;
#endif
  using ComplexIO = tchervinsky::Complex;
  using PairIO = tchervinsky::Pair;
  using StringIO = tchervinsky::String;
  using Keyfields = tchervinsky::KEYFIELDS;

  char c{ '\0' };
  in >> std::skipws >> tchervinsky::Delimiter{ '(' } >> std::noskipws;
  if (!in)
  {
    return in;
  }
  in >> std::noskipws >> tchervinsky::Delimiter{ ':' } >> std::noskipws;
  if (!in)
  {
    return in;
  }

  bool keyfields[static_cast<std::size_t>(Keyfields::KEYLEN)]{ false };
  for (std::size_t i = 0; i < static_cast<std::size_t>(Keyfields::KEYLEN); ++i)
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
        in >> ComplexIO{ dest.key1 };
        if (!in)
        {
          in.setstate(std::ios::failbit);
          return in;
        }
        keyfields[static_cast<std::size_t>(Keyfields::KEY1)] = true;
        break;
      }
      case '2':
      {
        in >> PairIO{ dest.key2 };
        if (!in)
        {
          in.setstate(std::ios::failbit);
          return in;
        }
        keyfields[static_cast<std::size_t>(Keyfields::KEY2)] = true;
        break;
      }
      case '3':
      {
        in >> StringIO{ dest.key3 };
        if (!in)
        {
          return in;
        }
        keyfields[static_cast<std::size_t>(Keyfields::KEY3)] = true;
        break;
      }
      default:
      {
        in.setstate(std::ios::failbit);
        return in;
      }
    }
  }
  in >> std::noskipws >> tchervinsky::Delimiter{ ')' };
  if (!in)
  {
    return in;
  }
  if (!
    (((keyfields[static_cast<std::size_t>(Keyfields::KEY1)]
    == keyfields[static_cast<std::size_t>(Keyfields::KEY2)])
    == keyfields[static_cast<std::size_t>(Keyfields::KEY3)])) == true)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}

std::ostream& tchervinsky::operator << (std::ostream& out, const tchervinsky::DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if(!sentry)
  {
    return out;
  }
  tchervinsky::StreamGuard guard(out);
  out << "(";
#if 0
  out << ":key2 " << src.key1 << 'l' << 'l';
#endif
  out << ":key1 " << "#c(" << std::fixed << std::setprecision(1) << src.key1.real() << " " << src.key1.imag() << ')';
//   (:N -1:D 5:)
  out << ":key2 " << "(:N " << std::setprecision(1) << src.key2.first << ":D " << std::setprecision(1) << src.key2.second << ":)";
  out << ":key3 " << '\"' << src.key3 << '\"';
  out << ":)";
  return out;
}

bool tchervinsky::operator < (const tchervinsky::DataStruct& a, const tchervinsky::DataStruct& b)
{
  if (a.key1 != b.key1)
  {
    double akey1mod = std::fabs(std::sqrt(std::pow(a.key1.real(), 2) + std::pow(a.key1.imag(), 2)));
    double bkey1mod = std::fabs(std::sqrt(std::pow(b.key1.real(), 2) + std::pow(b.key1.imag(), 2)));
    return akey1mod < bkey1mod;
  }
  else if (a.key2 != b.key2)
  {
    return a.key2 < b.key2;
  }
  else
  {
    return a.key3.size() < b.key3.size();
  }
}

#include <string>
#include <iostream>
#include <iterator>
#include <exception>
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

    std::string buff;
    std::getline(in, buff, ':');
    if (buff.size() < 6)
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    bool correctDouble = false;
    int buffSize = buff.size() & INT_MAX;
    for (int i = 0; i < buffSize; i++)
    {
      if (!(std::isdigit(buff[i])) && buff[i] != 'e' && buff[i] != 'E' && buff[i] == '+' && buff[i] == '-' && buff[i] == '.')
      {
        in.setstate(std::ios::failbit);
        return in;

      }
      if (buff[i] == 'e' || buff[i] == 'E')
      {
        if ((buff[i + 1] == '+' || buff[i + 1] == '-') && std::isdigit(buff[i - 1]) && std::isdigit(buff[i + 2]))
        {
          correctDouble = true;
        }
        else
        {
          in.setstate(std::ios::failbit);
          return in;
        }
      }
    }

    if (!correctDouble)
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    dest.ref = std::stod(buff);
    return in;
  }

  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest)
  {
    using del = DelimiterIO;
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string buffer;
    std::getline(in >> del{ '0' } >> del{ 'b' }, buffer, ':');
    try 
    {
      dest.ref = std::stoull(buffer);
    }
    catch (std::exception& e) 
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    using del = DelimiterIO;
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> del{ '"' }, dest.ref, '"');
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

    in >> sep{ '(' } >> sep{ ':' };
    std::string string;
    for (int i = 0; i < 3; i++)
    {
      std::getline(in, string, ' ');

      if (string == "key1")
      {
        in >> dbl{ input.key1 };
      }
      else if (string == "key2")
      {
        in >> ull{ input.key2 };
      }
      else if (string == "key3")
      {
        in >> str{ input.key3 };
      }
      else
      {
        in.setstate(std::ios::failbit);
        return in;
      }
    }
    in >> sep{ ':' } >> sep{ ')' };
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
    out << ":key2 0b" << ds.key2;
    out << ":key3 \"" << ds.key3 << '\"';
    out << ')';
    return out;
  }

  bool operator<(const DataStruct& left, const DataStruct& right) {
    if (left.key1 < right.key1)
    {
      return true;
    }
    else if (left.key1 == right.key1 && left.key2 < right.key2)
    {
      return true;
    }
    else if (left.key3.size() < right.key3.size())
    {
      return true;
    }
    return false;
  }
}

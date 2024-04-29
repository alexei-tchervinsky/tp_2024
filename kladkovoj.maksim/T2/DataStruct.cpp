#include <iostream>
#include <regex>
#include <iomanip>

#include "InputFormat.hpp"
#include "DataStruct.hpp"
#include "StreamGuard.hpp"

namespace kladkovoj
{
  bool operator<(const DataStruct& rhs, const DataStruct& lhs)
  {
    if (rhs.key1 != lhs.key1)
    {
      return rhs.key1 < lhs.key1;
    }
    if (rhs.key2 != lhs.key2)
    {
      return rhs.key2 < lhs.key2;
    }
    return rhs.key3.size() < lhs.key3.size();
  }

  std::istream& operator>>(std::istream& in, DataStruct& data)
  {
    std::istream::sentry sentry(in);
    if(!sentry)
    {
      return in;
    }
    StreamGuard ios_guard(in);
    {
      in >> DelimiterIO{ '(' };
      in >> DelimiterIO{ ':' };
      for(std::size_t i = 1; i <= 3; i++)
      {
        std::string key;
        in >> key;

        if (key == "key1")
        {
          in >> DoubleIO{ data.key1 };
          in >> DelimiterIO{ ':' };
        }

        else if (key == "key2")
        {
          in >> DelimiterIO{ '0' };
          if (in.peek() == 'b')
          {
            in >> DelimiterIO{ 'b' };
          }
          else
          {
              in >> DelimiterIO{ 'B' };
          }
          in >> LongLongBinIO{ data.key2 };
        }

        else if (key == "key3")
        {
          in >> StringIO{ data.key3 };
          in >> DelimiterIO{ ':' };
        }
        if(!sentry)
        {
          return in;
        }
      }
      in >> DelimiterIO{ ')' };
    }
    if (!in)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& data)
  {
    out << "(:key1 " << fromDoubleToScientific(data.key1);
    out << ":key2 0b" << fromULLtoBinary(data.key2);
    out << ":key3 \"" << data.key3 << "\":)";
    return out;
  }

  std::string fromDoubleToScientific(double val)
  {
    int exp = 0;
    if (val == 0 || std::abs(val) == 1)
      exp = 0;
    else if (std::abs(val) < 1)
    {
      while (std::abs(val) * 10 < 10)
      {
        val *= 10;
        exp--;
      }
    }
    else
    {
      while (std::abs(val) / 10 >= 1)
      {
        val /= 10;
        exp++;
      }
    }
    std::string res = std::to_string(val);
    res.erase(res.size()-4);
    std::string result = res + (exp < 0 ? "e-" : "e+") + std::to_string(std::abs(exp));
    return result;
  }

  std::string fromULLtoBinary(unsigned long long val)
  {
    if (val == 0)
    {
      return "0";
    }
    std::string binary;
    while (val > 0)
    {
      binary.insert(0, std::to_string(val % 2));
      val /= 2;
    }
    return binary;
  }
}


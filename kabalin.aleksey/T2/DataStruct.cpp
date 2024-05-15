#include "DataStruct.hpp"
#include "Guard.hpp"
#include <cmath>
#include <iostream>
namespace kabalin
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '\0';
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
    if(!sentry)
    {
      return in;
    }
    int mantissa = 0;
    int number = 0;
    int power = 0;
    in >> mantissa >> DelimiterIO{'.'} >> number;
    if (in.peek() == 'e')
    {
      in >> DelimiterIO{ 'e' };
    }
    else
    {
      in >> DelimiterIO{ 'E' };
    }
    in >> power;
    dest.ref = (mantissa * 1.0 + number * 0.01) * std::pow(10, power);
    return in;
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }
  std::istream &operator>>(std::istream &in, LITIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{'l'} >> DelimiterIO{'l'};
  }

  std::istream &operator>>(std::istream &in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{data}) && (data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
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
    if(res.find('0') == 2 && res[4] == '0')
    {
      res.erase(3);
    }
    else
    {
      res.erase(4);
    }
    std::string result = res + (exp < 0 ? "e-" : "e+") + std::to_string(std::abs(exp));
    return result;
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
      using lit = LITIO;
      using str = StringIO;
      using dbl = DoubleIO;
      in >> sep{ '(' };
      for(std::size_t i = 0; i < 3; i++)
      {
        in >> sep{ ':' };
        in >> characters;
        if (characters == "key1")
        {
          in >> dbl{ input.key1 };
        }
        else if (characters == "key2")
        {
          in >> lit{ input.key2 };
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
    iofmtguard fmtguard(out);
    out << "(:key1 " << fromDoubleToScientific(src.key1);
    out << ", :key2 " << src.key2 << "ll";
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
  }
}


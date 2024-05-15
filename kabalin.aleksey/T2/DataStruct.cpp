#include "DataStruct.hpp"
#include "Guard.hpp"
#include <cmath>
#include <iomanip>

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
    in >> std::dec >> dest.ref;
    if (in.peek() == 'l')
    {
      return in >> dest.ref >> DelimiterIO{'l'} >> DelimiterIO{'l'};
    }
    else
    {
      return in >> dest.ref >> DelimiterIO{'L'} >> DelimiterIO{'L'};
    }
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
    {
      using sep = DelimiterIO;
      using label = LabelIO;
      using dbl = DoubleIO;
      using str = StringIO;
      using LL = LITIO;
      in >> sep{'('};
      in >> label{"key1"} >> sep{':'} >> dbl{input.key1};
      in >> sep{','};
      in >> label{"key2"} >> sep{':'} >> LL{input.key2};
      in >> sep{','};
      in >> label{"key3"} >> sep{':'} >> str{input.key3};
      in >> sep{')'};
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
    out << "{ ";
    out << "\"key1\": " << std::fixed << std::setprecision(1) << fromDoubleToScientific(src.key1)<< ", ";
    out << "\"key2\": " << src.key2<<"LL";
    out << "\"key3\": " << src.key3;
    out << " }";
    return out;
  }
}


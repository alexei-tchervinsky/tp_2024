#include "DataStruct.hpp"

std::istream & leontiev::operator>>(std::istream & in, DataStruct & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimiterIO;
    using dbl = DoubleIO;
    using chr = CharIO;
    using str = StringIO;
    in >> sep{ '(' };
    std::string key;
    for (std::size_t i = 0; i < 3; ++i)
    {
      in >> sep{ ':' };
      in >> key;
      if (key == "key1")
      {
        in >> dbl{ input.key1 };
      }
      else if (key == "key2")
      {
        in >> chr{ input.key2 };
      }
      else if (key == "key3")
      {
        in >> str{ input.key3 };
      }
      else
      {
        in.setstate(std::ios::failbit);
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

bool leontiev::operator<(const DataStruct& firstOperand, const DataStruct& secondOperand)
{
  if (firstOperand.key1 != secondOperand.key1)
  {
    return firstOperand.key1 < secondOperand.key1;
  }
  if (firstOperand.key2 != secondOperand.key2)
  {
    return firstOperand.key2 < secondOperand.key2;
  }
  return firstOperand.key3.size() < secondOperand.key3.size();
}

std::ostream & leontiev::operator<<(std::ostream & out, const DataStruct & dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(:";
  out << "key1 " << std::fixed << std::setprecision(1) << dest.key1 << "d:";
  out << "key2 " << dest.key2 << "chr:";
  out << "key3 \"" << dest.key3 << "\":)";
  return out;
}

std::istream & leontiev::operator>>(std::istream & in, DoubleIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref >> DelimiterIO { 'd' };
}

std::istream & leontiev::operator>>(std::istream & in, CharIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> DelimiterIO{ '"' } >> dest.ref  >> DelimiterIO{ '"' };
}

std::istream & leontiev::operator>>(std::istream & in, StringIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& leontiev::operator>>(std::istream& in, DelimiterIO&& dest)
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

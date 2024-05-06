#include "DataStruct.hpp"
#include "Struct.hpp"

std::istream & gredasov::operator>>(std::istream & in, DataStruct & dest)
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
    using ll = LongLongIO;
    using str = StringIO;
    in >> sep{ '(' };
    std::string keyX;
    for (std::size_t i = 0; i < 3; ++i)
    {
      in >> sep{ ':' } >> keyX;
      if (keyX == "key1")
      {
        in >> dbl{ input.key1 };
      }
      else if (keyX == "key2")
      {
        in >> ll{ input.key2 };
      }
      else if (keyX == "key3")
      {
        in >> str{ input.key3 };
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    in >> sep{ ':' } >> sep{ ')' };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream & gredasov::operator<<(std::ostream & out, const DataStruct & dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(:";
  out << "key1 " << std::fixed << std::setprecision(1) << dest.key1 << "d:";
  out << "key2 " << dest.key2 << "ll:";
  out << "key3 " << '"' << dest.key3 << '"' << ":)";
  return out;
}

bool gredasov::operator<(const DataStruct& toCompare, const DataStruct& otherToCompare)
{
  if (toCompare.key1 != otherToCompare.key1)
  {
    return toCompare.key1 < otherToCompare.key1;
  }
  if (toCompare.key2 != otherToCompare.key2)
  {
    return toCompare.key2 < otherToCompare.key2;
  }
  return toCompare.key3.size() < otherToCompare.key3.size();
}


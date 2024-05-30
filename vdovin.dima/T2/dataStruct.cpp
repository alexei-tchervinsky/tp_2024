#include "dataStruct.h"
#include <iostream>
#include <iomanip>
#include "delimiter.h"
#include "streamGuard.h"
namespace vdovin
{
  bool operator<(const DataStruct& lhs, const DataStruct& rhs)
  {
    if (lhs.key1 != rhs.key1)
    {
      return lhs.key1 < rhs.key1;
    }
    if (lhs.key2 != rhs.key2)
    {
      return lhs.key2 < rhs.key2;
    }
    return lhs.key3.size() < rhs.key3.size();
  }

  std::istream& operator>>(std::istream& in, DataStruct& data)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    StreamGuard s_guard(in);
    using del = vdovin::Delimiter;
    in >> del{ '(' };
    for (int b = 0; b < 3; b++)
    {
      in >> del{ ':' } >> del{ 'k' } >> del{ 'e' } >> del{ 'y' };
      int i = 0;
      in >> i;
      if (i == 1)
      {
        double value = 0;
        in >> value;
        data.key1 = value;
        in >> del{ 'd' };
      }
      else if (i == 2)
      {
        long long value = 0;
        in >> value;
        data.key2 = value;
        in >> del{ 'l' } >> del{ 'l' };
      }
      else if (i == 3)
      {
        std::string value = "";
        in >> del{ '"' };
        std::getline(in, value, '\"');
        data.key3 = value;
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    in >> del{ ':' } >> del{ ')' };
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& data)
  {
    std::ostream::sentry guard(out);
    if (!guard)
    {
      return out;
    }
    StreamGuard s_guard(out);
    out << std::fixed;
    out << "(:key1 " << std::setprecision(1) << data.key1 << "d:key2 " << data.key2 << "ll:key3 \"" << data.key3 << "\":)";
    return out;
  }
}

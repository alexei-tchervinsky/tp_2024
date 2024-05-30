#include "delimiter.h"
#include <iostream>
#include "streamGuard.h"

namespace vdovin
{
  std::istream& operator>>(std::istream& in, Delimiter&& exp)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    StreamGuard s_guard(in);
    char c = 0;
    in >> c;
    if (c != exp.expected)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}


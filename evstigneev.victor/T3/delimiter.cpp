#include "Delimiter.hpp"

namespace evstigneev
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    if (c != dest.del)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
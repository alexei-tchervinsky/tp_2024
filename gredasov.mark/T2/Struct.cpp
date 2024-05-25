#include "Struct.hpp"
#include "Delimiter.hpp"

std::istream & gredasov::operator>>(std::istream & in, DoubleIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref >> DelimiterIO { 'd' };
}

std::istream & gredasov::operator>>(std::istream & in, LongLongIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
}

std::istream & gredasov::operator>>(std::istream & in, StringIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}


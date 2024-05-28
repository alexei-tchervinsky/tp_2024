#include "IOstructures.hpp"
#include <iostream>
#include "DelimiterIO.hpp"
#include "UllOctIO.hpp"
#include "UllLitIO.hpp"
#include "StringIO.hpp"
#include "DataStruct.hpp"
std::istream & lelkov::operator>>(std::istream & in, DelimiterIO && value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char ch = 0;
  in >> ch;
  if (ch != value.exp)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & lelkov::operator>>(std::istream & in, UllLitIO && value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> value.ref >> DelimiterIO{'u'} >> DelimiterIO{'l'} >> DelimiterIO{'l'};
}

std::istream & lelkov::operator>>(std::istream & in, UllOctIO && value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = DelimiterIO;
  in >> del{'0'};
  return in >> std::oct >> value.ref;
}

std::istream & lelkov::operator>>(std::istream & in, StringIO && value)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, value.str, '"');
}

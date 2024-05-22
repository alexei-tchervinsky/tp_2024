#include "polygon.hpp"
#include "delimiter.hpp"

std::istream & gredasov::operator>>(std::istream & in, Point & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int x, y;
  in >> DelimiterIO{ '(' } >> x >> DelimiterIO{ ';' } >> y >> DelimiterIO{ ')' };
  if (in)
  {
    dest.x = x;
    dest.y = y;
  }
  return in;
}

std::istream & gredasov::operator>>(std::istream & in, Polygon & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t pointCount = 0;
  if (!(in >> pointCount) || pointCount <= 2)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > polygon;
  Point point;
  for (size_t i = 0; i < pointCount; ++i)
  {
    if (in.get() == '\n')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    if (in >> point)
    {
      polygon.push_back(point);
    }
  }
  if (in && polygon.size() == pointCount && in.get() == '\n')
  {
    dest = Polygon{ polygon };
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}


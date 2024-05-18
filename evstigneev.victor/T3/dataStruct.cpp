#include "dataStruct.hpp"
#include "delimiter.hpp"

std::istream& evstigneev::operator>>(std::istream& in, evstigneev::Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = DelimiterIO;
  Point point;
  in >> del{ '(' } >> point.x >> del{ ';' } >> point.y >> del{ ')' };
  if (in)
  {
    dest = point;
  }
  return in;
}

std::istream& evstigneev::operator>>(std::istream& in, evstigneev::Polygon& poly)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Polygon polygon;
  size_t vexes;
  if (!(in >> vexes))
  {
    in.setstate(std::ios::failbit);
  }
  Point point;
  for (size_t i = 0; i < vexes; i++)
  {
    in >> point;
    if (in)
    {
      polygon.points.push_back(point);
    }
  }
  if (in)
  {
    poly = polygon;
  }
  return in;
}

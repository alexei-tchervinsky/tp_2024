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
  int x = 0, y = 0;
  in >> del{ '(' } >> x >> del{ ';' } >> y >> del{ ')' };
  if (in)
  {
    dest.x = x;
    dest.y = y;
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
  size_t vexes = 0;
  if (!(in >> vexes) || vexes <=2 )
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  Point point;
  for (size_t i = 0; i < vexes; i++)
  {
    if (in.get() == '\n')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> point;
    if (in)
    {
      polygon.points.push_back(point);
    }
  }
  if (in && polygon.points.size() == vexes && in.get() == '\n')
  {
    poly = polygon;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

bool evstigneev::operator==(const Polygon& fp, const Polygon& sp)
{
  if (fp.points.size() != sp.points.size())
  {
    return false;
  }
  for (size_t i = 0; i < fp.points.size(); ++i)
  {
    if (fp.points[i].x != sp.points[i].x || fp.points[i].y != sp.points[i].y)
    {
      return false;
    }
  }
  return true;
}

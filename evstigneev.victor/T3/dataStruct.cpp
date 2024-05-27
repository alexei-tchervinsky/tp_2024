#include "dataStruct.hpp"
#include "delimiter.hpp"
#include <algorithm>
#include <sstream>
#include <numeric>

bool evstigneev::Point::operator==(const Point& rhs) const
{
  return x == rhs.x && y == rhs.y;
}

std::istream& evstigneev::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point temp;
  in >> temp.x >> DelimiterIO{ ';' } >> temp.y;
  dest = temp;
  return in;
}

std::istream& evstigneev::operator>>(std::istream& in, Polygon& poly)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Polygon polygon;
  size_t vexes = 0;
  if (!(in >> vexes) || vexes < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  for (size_t i = 0; i < vexes; i++)
  {
    Point point;
    in >> DelimiterIO{ '(' } >> point >> DelimiterIO{ ')' };
    if (in)
    {
      polygon.points.push_back(point);
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  if (in && polygon.points.size() == vexes && in.get() == '\n')
  {
    poly = polygon;
  }
  return in;
}

std::ostream& evstigneev::operator<<(std::ostream& out,
  const evstigneev::Point& dest)
{
  return out << '(' << dest.x << ';' << dest.y << ')';
}
std::ostream& evstigneev::operator<<(std::ostream& out,
  const Polygon& poly)
{
  out << poly.points.size();
  for (auto& point : poly.points)
  {
    out << ' ' << point;
  }
  return out << '\n';
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

bool evstigneev::Polygon::operator<(const Polygon& p) const
{
  return getArea() < p.getArea();
}

double evstigneev::Polygon::getArea() const
{
  double area = 0.0;
  for (size_t i = 0; i < points.size(); ++i) {
    size_t next = (i + 1) % points.size();
    area += points[i].x * points[next].y - points[i].y * points[next].x;
  }
  return std::abs(area) / 2.0;
}

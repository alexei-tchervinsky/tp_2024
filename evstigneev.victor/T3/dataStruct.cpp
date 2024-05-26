#include "dataStruct.hpp"
#include "delimiter.hpp"
#include <algorithm>
#include <sstream>
#include <numeric>

std::istream& evstigneev::operator>>(std::istream& in, evstigneev::Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string str;
  in >> str;
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  char c;
  std::stringstream s(str);
  s >> c >> dest.x >> c >> dest.y >> c;
  return in;
}

std::istream& evstigneev::operator>>(std::istream& in, evstigneev::Polygon& poly)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  poly.points.clear();
  size_t vexes = 0;
  if (!(in >> vexes) || vexes < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  poly.points.resize(vexes);
  for (auto &point : poly.points)
  {
    if (in.get() == '\n')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> point;
  }
  if (in.get() != '\n')
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& evstigneev::operator<<(std::ostream& out,
  const evstigneev::Point& dest)
{
  return out << '(' << dest.x << ';' << dest.y << ')';
}
std::ostream& operator<<(std::ostream& out,
  const evstigneev::Polygon& poly)
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

bool evstigneev::operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

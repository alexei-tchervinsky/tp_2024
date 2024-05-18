#include "DataStruct.hpp"
#include "Delimiter.hpp"
#include <functional>
#include <numeric>
#include <algorithm>

bool evstigneev::Point::operator==(Point& p)
{
  return (x = p.x) && (y == p.y);
}

double evstigneev::Polygon::getArea()
{
  auto cArea = std::bind(CArea{ points[1] }, std::placeholders::_1, 
    std::placeholders::_2, points[0]);
  return std::accumulate(points.begin(), points.end(), 0.0, cArea);
}

int evstigneev::Polygon::countAngle()
{
  auto cAngle = CAngle{ points[points.size() - 1], points[points.size() - 2] };

  return std::count_if(points.cbegin(), points.cend(), cAngle);
}

double evstigneev::CArea::operator()(double d, Point& p1, Point& p2)
{
  d += 0.5 * std::abs((p2.x - point_.x) * (p1.y - point_.y) - 
    (p1.x - point_.x) * (p2.y - point_.y));
  point_ = p1;
  return d;
}

bool evstigneev::CAngle::operator()(Point& p_)
{
  Point s1 = { point_2.x - point_1.x, point_2.y - point_1.y };
  Point s2 = { p_.x - point_1.x, p_.y - point_1.y };

  point_1 = point_2;
  point_2 = p_;

  return s1.x * s2.x + s1.y * s2.y == 0;
}

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

#include "struct.hpp"
#include <iostream>
#include <limits>
#include "delimiter.hpp"

std::istream& lelkov::operator>>(std::istream& in, Point& applicant)
{
  std::istream::sentry guard(in);
  Point point;
  if (!guard)
  {
    return in;
  }
  in >> DelimiterIO{ '(' } >> point.x >> DelimiterIO{ ';' } >> point.y >> DelimiterIO{ ')' };
  if (in)
  {
    applicant = point;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& lelkov::operator>>(std::istream& in, Polygon& applicant)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Polygon polygon;
  Point point;
  size_t vertices = 0;
  in >> vertices;
  if (!in || vertices < 3)
  {
    in.setstate(std::ios::failbit);
  }
  for (size_t i = 0; i < vertices + 1; i++)
  {
    std::istream::pos_type startPos = in.tellg();
    if (!(in >> point))
    {
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      in.seekg(startPos);
      break;
    }
    else
    {
      polygon.points.push_back(point);
    }
  }
  if (vertices == polygon.points.size())
  {
    applicant = polygon;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

bool lelkov::operator==(const Point& left, const Point& right)
{
  return (left.x == right.x) && (left.y == right.y);
}

bool lelkov::operator!=(const Point& left, const Point& right)
{
  return (left.x != right.x) || (left.y != right.y);
}

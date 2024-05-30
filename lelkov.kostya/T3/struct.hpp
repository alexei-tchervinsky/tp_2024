#ifndef STRUCT_HPP
#define STRUCT_HPP
#include <iosfwd>
#include <vector>

namespace lelkov
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& applicant);
  std::istream& operator>>(std::istream& in, Polygon& applicant);
  bool operator==(const Point& left, const Point& right);
  bool operator!=(const Point& left, const Point& right);
}

#endif

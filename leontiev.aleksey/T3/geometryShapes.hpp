#ifndef GEOMETRY_SHAPES_HPP
#define GEOMETRY_SHAPES_HPP

#include <vector>
#include <iostream>


namespace leontiev
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector<Point> points;
  };

  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
  bool operator==(const Point& first, const Point& second);
  bool operator==(const Polygon& first, const Polygon& second);
}

#endif

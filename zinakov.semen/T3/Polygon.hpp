#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>
#include <iostream>

namespace semzin
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector<Point> points;
  };

  struct DelimiterIO
  {
    char del;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, Point &dest);
  std::istream &operator>>(std::istream &in, Polygon &dest);
}
#endif

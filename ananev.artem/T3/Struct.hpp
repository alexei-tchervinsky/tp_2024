#ifndef STRUCT_HPP
#define STRUCT_HPP
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

namespace ananev
{
  struct DelimiterIO
  {
    char del;
  };

  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, Point &dest);
  std::istream &operator>>(std::istream &in, Polygon &dest);
  double area(const Polygon& polygon);
}
#endif

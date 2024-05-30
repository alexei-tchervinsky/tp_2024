#ifndef STRUCT_HPP
#define STRUCT_HPP
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
#include <exception>
#include <iterator>
#include <algorithm>
#include <map>
#include <functional>
#include <numeric>
#include <cmath>

namespace grudov
{
  struct DelimiterIO
  {
    char del;
  };

  struct Point
  {
    int x_, y_;
    bool operator==(const Point& other) const;
  };

  struct Polygon
  {
    std::vector< Point > points_;
    bool operator==(const Polygon& other) const;
  };
  double areaPolygon(const Polygon& polygon);
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, Point &dest);
  std::istream &operator>>(std::istream &in, Polygon &dest);
}
#endif

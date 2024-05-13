#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace ananjeva {
  struct Point {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& dest);
  bool operator==(const Point& lhs, const Point& rhs);

  struct Polygon {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& dest);
  bool operator==(const Polygon& lhs, const Polygon& rhs);
}



#endif

#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace ananjeva {
  struct Point {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& dest);

  struct Polygon {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& dest);
}

#endif

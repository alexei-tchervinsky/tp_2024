#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

namespace kabalin {
struct Point {
  double x, y;

  bool operator==(const Point &other) const;
};

class Polygon {
public:
  std::vector<Point> points;
};

std::istream &operator>>(std::istream &in, Polygon &polygon);

}; // namespace kabalin

#endif // POLYGON_HPP

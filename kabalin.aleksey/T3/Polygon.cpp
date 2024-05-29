#include "Polygon.hpp"
#include <cmath>

namespace kabalin {
bool Point::operator==(const Point &other) const {
  return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9;
}

std::istream &operator>>(std::istream &is, Polygon &polygon) {
  size_t numPoints;
  is >> numPoints;
  polygon.points.resize(numPoints);
  for (size_t i = 0; i < numPoints; ++i) {
    is >> polygon.points[i].x >> polygon.points[i].y;
  }
  return is;
}
} // namespace kabalin

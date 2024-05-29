#include "Polygon.hpp"
#include <cmath>

namespace kabalin {
bool Point::operator==(const Point &other) const {
  return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9;
}

std::istream &operator>>(std::istream &in, kabalin::Polygon &polygon) {
  std::size_t pointCount;
  if (!(in >> pointCount)) {
    throw std::invalid_argument("Failed to read point count");
  }
  polygon.points.resize(
      pointCount); // Инициализируем вектор точек перед использованием
  for (std::size_t i = 0; i < pointCount; ++i) {
    if (!(in >> polygon.points[i].x >> polygon.points[i].y)) {
      throw std::invalid_argument("Failed to read point coordinates");
    }
  }
  return in;
}
} // namespace kabalin

#include "Polygon.hpp"
#include <cmath>
#include <sstream>

namespace kabalin {
bool Point::operator==(const Point &other) const {
  return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9;
}

std::istream &operator>>(std::istream &in, Polygon &polygon) {
  std::string line;
  if (!std::getline(in, line)) {
    throw std::invalid_argument("Failed to read line");
  }

  std::istringstream iss(line);
  std::size_t pointCount;
  char delim;
  if (!(iss >> pointCount)) {
    throw std::invalid_argument("Failed to read point count");
  }

  if (!(iss >> delim) || delim != '(') {
    throw std::invalid_argument("Failed to read '('");
  }

  polygon.points.resize(pointCount); // Initialize the vector before using it

  for (std::size_t i = 0; i < pointCount; ++i) {
    if (!(iss >> polygon.points[i].x)) {
      throw std::invalid_argument("Failed to read x coordinate");
    }

    if (!(iss >> delim) || delim != ';') {
      throw std::invalid_argument("Failed to read ';'");
    }

    if (!(iss >> polygon.points[i].y)) {
      throw std::invalid_argument("Failed to read y coordinate");
    }

    if (!(iss >> delim) || delim != ')') {
      throw std::invalid_argument("Failed to read ')'");
    }
  }
  return in;
}

} // namespace kabalin

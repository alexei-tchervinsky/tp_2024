#include "polygon.hpp"
#include <algorithm>
#include <fstream>
#include <limits>
#include <stdexcept>

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

double polygonArea(const kabalin::Polygon &polygon) {
  double area = 0.0;
  int n = polygon.points.size();
  for (int i = 0; i < n; ++i) {
    const auto &p1 = polygon.points[i];
    const auto &p2 = polygon.points[(i + 1) % n];
    area += (p1.x * p2.y) - (p2.x * p1.y);
  }
  return std::abs(area) / 2.0;
}

bool arePolygonsEqual(const kabalin::Polygon &a, const kabalin::Polygon &b) {
  if (a.points.size() != b.points.size()) {
    return false;
  }

  for (std::size_t i = 0; i < a.points.size(); ++i) {
    if (!(a.points[i] == b.points[i])) {
      return false;
    }
  }
  return true;
}

double sumAreaByVertexType(const std::vector<kabalin::Polygon> &polygons,
                           bool even) {
  double sum = 0.0;
  for (const auto &polygon : polygons) {
    if (even && polygon.points.size() % 2 == 0) {
      sum += polygonArea(polygon);
    } else if (!even && polygon.points.size() % 2 != 0) {
      sum += polygonArea(polygon);
    }
  }
  return sum;
}

double meanArea(const std::vector<kabalin::Polygon> &polygons) {
  if (polygons.empty()) {
    throw std::invalid_argument("No polygons available to calculate mean area");
  }
  double totalArea = 0.0;
  for (const auto &polygon : polygons) {
    totalArea += polygonArea(polygon);
  }
  return totalArea / polygons.size();
}

double sumAreaByVertexCount(const std::vector<kabalin::Polygon> &polygons,
                            std::size_t vertexCount) {
  double sum = 0.0;
  for (const auto &polygon : polygons) {
    if (polygon.points.size() == vertexCount) {
      sum += polygonArea(polygon);
    }
  }
  return sum;
}

double getMaxArea(const std::vector<kabalin::Polygon> &polygons) {
  if (polygons.empty()) {
    throw std::invalid_argument("No polygons available to calculate max area");
  }
  return polygonArea(*std::max_element(
      polygons.begin(), polygons.end(),
      [](const kabalin::Polygon &a, const kabalin::Polygon &b) {
        return polygonArea(a) < polygonArea(b);
      }));
}

std::size_t getMaxVertexes(const std::vector<kabalin::Polygon> &polygons) {
  if (polygons.empty()) {
    throw std::invalid_argument(
        "No polygons available to calculate max vertexes");
  }
  return std::max_element(
             polygons.begin(), polygons.end(),
             [](const kabalin::Polygon &a, const kabalin::Polygon &b) {
               return a.points.size() < b.points.size();
             })
      ->points.size();
}

double getMinArea(const std::vector<kabalin::Polygon> &polygons) {
  if (polygons.empty()) {
    throw std::invalid_argument("No polygons available to calculate min area");
  }
  return polygonArea(*std::min_element(
      polygons.begin(), polygons.end(),
      [](const kabalin::Polygon &a, const kabalin::Polygon &b) {
        return polygonArea(a) < polygonArea(b);
      }));
}

std::size_t getMinVertexes(const std::vector<kabalin::Polygon> &polygons) {
  if (polygons.empty()) {
    throw std::invalid_argument(
        "No polygons available to calculate min vertexes");
  }
  return std::min_element(
             polygons.begin(), polygons.end(),
             [](const kabalin::Polygon &a, const kabalin::Polygon &b) {
               return a.points.size() < b.points.size();
             })
      ->points.size();
}

int countPolygonsByVertexType(const std::vector<kabalin::Polygon> &polygons,
                              bool even) {
  return std::count_if(polygons.begin(), polygons.end(),
                       [even](const kabalin::Polygon &polygon) {
                         return (even && polygon.points.size() % 2 == 0) ||
                                (!even && polygon.points.size() % 2 != 0);
                       });
}

int countPolygonsByVertexCount(const std::vector<kabalin::Polygon> &polygons,
                               std::size_t vertexCount) {
  return std::count_if(polygons.begin(), polygons.end(),
                       [vertexCount](const kabalin::Polygon &polygon) {
                         return polygon.points.size() == vertexCount;
                       });
}

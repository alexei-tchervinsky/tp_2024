#include "Utilities.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>

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
  return std::accumulate(
      polygons.begin(), polygons.end(), 0.0,
      [even](double sum, const kabalin::Polygon &polygon) {
        return sum + ((even && polygon.points.size() % 2 == 0) ||
                              (!even && polygon.points.size() % 2 != 0)
                          ? polygonArea(polygon)
                          : 0.0);
      });
}

double meanArea(const std::vector<kabalin::Polygon> &polygons) {
  if (polygons.empty()) {
    throw std::invalid_argument("No polygons available to calculate mean area");
  }
  double totalArea =
      std::accumulate(polygons.begin(), polygons.end(), 0.0,
                      [](double sum, const kabalin::Polygon &polygon) {
                        return sum + polygonArea(polygon);
                      });
  return totalArea / polygons.size();
}

double sumAreaByVertexCount(const std::vector<kabalin::Polygon> &polygons,
                            std::size_t vertexCount) {
  return std::accumulate(
      polygons.begin(), polygons.end(), 0.0,
      [vertexCount](double sum, const kabalin::Polygon &polygon) {
        return sum + (polygon.points.size() == vertexCount
                          ? polygonArea(polygon)
                          : 0.0);
      });
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

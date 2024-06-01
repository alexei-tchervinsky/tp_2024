#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

namespace kabalin {
struct Point {
  int x, y;
  bool operator==(const Point &other) const;
  bool operator<(const Point &other) const {
    return std::tie(x, y) < std::tie(other.x, other.y);
  }
};

struct Polygon {
  std::vector<Point> points;
};

struct DelimiterIO {
  char del;
};

std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
std::istream &operator>>(std::istream &in, Point &dest);
std::istream &operator>>(std::istream &in, Polygon &dest);
double polygonArea(const kabalin::Polygon &polygon);

bool arePolygonsEqual(const kabalin::Polygon &a, const kabalin::Polygon &b);

double sumAreaByVertexType(const std::vector<kabalin::Polygon> &polygons,
                           bool even);

double meanArea(const std::vector<kabalin::Polygon> &polygons);

double sumAreaByVertexCount(const std::vector<kabalin::Polygon> &polygons,
                            std::size_t vertexCount);

double getMaxArea(const std::vector<kabalin::Polygon> &polygons);

std::size_t getMaxVertexes(const std::vector<kabalin::Polygon> &polygons);

double getMinArea(const std::vector<kabalin::Polygon> &polygons);

std::size_t getMinVertexes(const std::vector<kabalin::Polygon> &polygons);

int countPolygonsByVertexType(const std::vector<kabalin::Polygon> &polygons,
                              bool even);

int countPolygonsByVertexCount(const std::vector<kabalin::Polygon> &polygons,
                               std::size_t vertexCount);
bool areAllPointsUnique(const Polygon &polygon);
} // namespace kabalin
#endif // POLYGON_HPP

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "Polygon.hpp"
#include <vector>

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

#endif // UTILITIES_HPP

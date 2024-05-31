#include "Commands.hpp"
#include <algorithm>
#include <iomanip>
#include <tuple>
namespace kabalin {
void area_command(const std::vector<kabalin::Polygon> &polygons,
                  std::istream &in, std::ostream &out) {
  std::string param;
  in >> param;
  if (param == "EVEN") {
    out << std::setprecision(1) << sumAreaByVertexType(polygons, true) << '\n';
  } else if (param == "ODD") {
    out << std::setprecision(1) << sumAreaByVertexType(polygons, false) << '\n';
  } else if (param == "MEAN") {
    out << std::setprecision(1) << meanArea(polygons) << '\n';
  } else {
    std::size_t vertexCount = std::stoi(param);
    out << std::setprecision(1) << sumAreaByVertexCount(polygons, vertexCount)
        << '\n';
  }
}

void max_command(const std::vector<kabalin::Polygon> &polygons,
                 std::istream &in, std::ostream &out) {
  std::string param;
  in >> param;
  if (param == "AREA") {
    out << std::setprecision(1) << getMaxArea(polygons) << '\n';
  } else if (param == "VERTEXES") {
    out << getMaxVertexes(polygons) << '\n';
  }
}

void less_area_command(const std::vector<kabalin::Polygon> &polygons,
                       std::istream &in, std::ostream &out) {
  kabalin::Polygon referencePolygon;
  in >> referencePolygon;
  double referenceArea = polygonArea(referencePolygon);

  int count = 0;
  for (const auto &polygon : polygons) {
    if (polygonArea(polygon) < referenceArea) {
      ++count;
    }
  }
  out << count << '\n';
}

void min_command(const std::vector<kabalin::Polygon> &polygons,
                 std::istream &in, std::ostream &out) {
  std::string param;
  in >> param;
  if (param == "AREA") {
    out << std::setprecision(1) << getMinArea(polygons) << '\n';
  } else if (param == "VERTEXES") {
    out << getMinVertexes(polygons) << '\n';
  }
}

void count_command(const std::vector<kabalin::Polygon> &polygons,
                   std::istream &in, std::ostream &out) {
  std::string param;
  in >> param;
  if (param == "EVEN") {
    out << countPolygonsByVertexType(polygons, true) << '\n';
  } else if (param == "ODD") {
    out << countPolygonsByVertexType(polygons, false) << '\n';
  } else {
    std::size_t vertexCount = std::stoi(param);
    out << countPolygonsByVertexCount(polygons, vertexCount) << '\n';
  }
}

void same_area_command(const std::vector<kabalin::Polygon> &polygons,
                       std::istream &in, std::ostream &out) {
  kabalin::Polygon referencePolygon;
  in >> referencePolygon;

  int count = 0;
  for (const auto &polygon : polygons) {
    if (arePolygonsCompatible(polygon, referencePolygon)) {
      ++count;
    }
  }
  out << count << '\n';
}
} // namespace kabalin

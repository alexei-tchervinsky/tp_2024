#include "Commands.hpp"
#include "Utilities.hpp"
#include <algorithm>
#include <iomanip>
#include <limits>
#include <stdexcept>

void less_area_command(const std::vector<kabalin::Polygon> &polygons,
                       std::istream &in, std::ostream &out) {
  std::string param;
  in >> param;
  double threshold = std::stod(param);

  double sumArea = 0.0;
  for (const auto &polygon : polygons) {
    double area = polygonArea(polygon);
    if (area < threshold) {
      sumArea += area;
    }
  }
  out << std::setprecision(1) << sumArea << '\n';
}

void same_area_command(const std::vector<kabalin::Polygon> &polygons,
                       std::istream &in, std::ostream &out) {
  std::string polygonIndexStr;
  in >> polygonIndexStr;
  int polygonIndex = std::stoi(polygonIndexStr);
  if (polygonIndex < 0 || polygonIndex >= static_cast<int>(polygons.size())) {
    throw std::invalid_argument("<INVALID INDEX>");
  }
  const kabalin::Polygon &polygon = polygons[polygonIndex];
  int count = 0;
  for (const auto &p : polygons) {
    if (arePolygonsEqual(p, polygon)) {
      count++;
    }
  }
  out << count << '\n';
}

void area_command(const std::vector<kabalin::Polygon> &polygons,
                  std::istream &in, std::ostream &out) {
  std::string param;
  in >> param;
  if (param == "ODD") {
    out << std::setprecision(1) << sumAreaByVertexType(polygons, false) << '\n';
  } else if (param == "EVEN") {
    out << std::setprecision(1) << sumAreaByVertexType(polygons, true) << '\n';
  } else if (param == "MEAN") {
    out << std::setprecision(1) << meanArea(polygons) << '\n';
  } else {
    std::size_t vertexCount = std::stoul(param);
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
  } else {
    throw std::invalid_argument("<INVALID PARAMETER>");
  }
}

void min_command(const std::vector<kabalin::Polygon> &polygons,
                 std::istream &in, std::ostream &out) {
  std::string param;
  in >> param;
  if (param == "AREA") {
    out << std::setprecision(1) << getMinArea(polygons) << '\n';
  } else if (param == "VERTEXES") {
    out << getMinVertexes(polygons) << '\n';
  } else {
    throw std::invalid_argument("<INVALID PARAMETER>");
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
    std::size_t vertexCount = std::stoul(param);
    out << countPolygonsByVertexCount(polygons, vertexCount) << '\n';
  }
}

void ioUI(const std::vector<kabalin::Polygon> &polygons, std::istream &in,
          std::ostream &out) {
  std::string command;
  in >> command;
  if (command == "LESSAREA") {
    less_area_command(polygons, in, out);
  } else if (command == "SAME") {
    same_area_command(polygons, in, out);
  } else if (command == "AREA") {
    area_command(polygons, in, out);
  } else if (command == "MAX") {
    max_command(polygons, in, out);
  } else if (command == "MIN") {
    min_command(polygons, in, out);
  } else if (command == "COUNT") {
    count_command(polygons, in, out);
  } else {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

#include "Commands.hpp"
#include <algorithm>
#include <exception>
#include <iomanip>
#include <stdexcept>
#include <tuple>
namespace kabalin {
void area_command(const std::vector<kabalin::Polygon> &polygons,
                  std::istream &in, std::ostream &out) {
  std::string param;
  in >> param;
  try {
    if (param == "EVEN") {
      out << std::setprecision(1) << sumAreaByVertexType(polygons, true)
          << '\n';
    } else if (param == "ODD") {
      out << std::setprecision(1) << sumAreaByVertexType(polygons, false)
          << '\n';
    } else if (param == "MEAN") {
      out << std::setprecision(1) << meanArea(polygons) << '\n';
    } else {
      std::size_t vertexCount = std::stoi(param);
      if (vertexCount >= 3) {
        out << std::setprecision(1)
            << sumAreaByVertexCount(polygons, vertexCount) << '\n';
      } else {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
  } catch (std::exception &ex) {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void max_command(const std::vector<kabalin::Polygon> &polygons,
                 std::istream &in, std::ostream &out) {
  std::string param;
  in >> param;
  try {
    if (param == "AREA") {
      out << std::setprecision(1) << getMaxArea(polygons) << '\n';
    } else if (param == "VERTEXES") {
      out << getMaxVertexes(polygons) << '\n';
    } else {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  } catch (std::exception &ex) {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void less_area_command(const std::vector<kabalin::Polygon> &polygons,
                       std::istream &in, std::ostream &out) {
  kabalin::Polygon referencePolygon;
  in >> referencePolygon;
  if (!in) {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
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
  try {
    if (param == "AREA") {
      out << std::setprecision(1) << getMinArea(polygons) << '\n';
    } else if (param == "VERTEXES") {
      out << getMinVertexes(polygons) << '\n';
    } else {
      throw std::invalid_argument("<INVALID COMMANND>");
    }
  } catch (std::exception &ex) {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void count_command(const std::vector<kabalin::Polygon> &polygons,
                   std::istream &in, std::ostream &out) {
  std::string param;
  in >> param;
  try {
    if (param == "EVEN") {
      out << countPolygonsByVertexType(polygons, true) << '\n';
    } else if (param == "ODD") {
      out << countPolygonsByVertexType(polygons, false) << '\n';
    } else {
      std::size_t vertexCount = std::stoi(param);
      if (vertexCount >= 3) {
        out << countPolygonsByVertexCount(polygons, vertexCount) << '\n';
      } else {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
  } catch (std::exception &ex) {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void same_area_command(const std::vector<kabalin::Polygon> &polygons,
                       std::istream &in, std::ostream &out) {
  kabalin::Polygon referencePolygon;
  in >> referencePolygon;
  if (!in) {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  int count = 0;
  for (const auto &polygon : polygons) {
    if (arePolygonsCompatible(polygon, referencePolygon)) {
      ++count;
    }
  }
  out << count << '\n';
}
} // namespace kabalin

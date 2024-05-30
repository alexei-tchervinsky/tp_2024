#include "polygon.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include <vector>

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

bool arePolygonsCompatible(const kabalin::Polygon &a,
                           const kabalin::Polygon &b) {
  if (a.points.size() != b.points.size()) {
    return false;
  }

  std::vector<kabalin::Point> translatedA = a.points;
  std::vector<kabalin::Point> translatedB = b.points;

  // Translate both polygons to have their first point at (0,0)
  auto translateToOrigin = [](std::vector<kabalin::Point> &points) {
    double dx = points[0].x;
    double dy = points[0].y;
    for (auto &p : points) {
      p.x -= dx;
      p.y -= dy;
    }
  };

  translateToOrigin(translatedA);
  translateToOrigin(translatedB);

  // Sort points to compare them directly
  std::sort(translatedA.begin(), translatedA.end(),
            [](const kabalin::Point &a, const kabalin::Point &b) {
              return std::tie(a.x, a.y) < std::tie(b.x, b.y);
            });
  std::sort(translatedB.begin(), translatedB.end(),
            [](const kabalin::Point &a, const kabalin::Point &b) {
              return std::tie(a.x, a.y) < std::tie(b.x, b.y);
            });

  return std::equal(translatedA.begin(), translatedA.end(),
                    translatedB.begin());
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

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "FILENAME_NOT_SPECIFIED\n";
    return 1;
  }
  std::ifstream in;
  in.open(argv[1]);
  if (!in) {
    std::cerr << "FILE_NOT_FOUND\n";
    return 1;
  }
  std::vector<kabalin::Polygon> polygons;
  while (!in.eof()) {
    std::copy(std::istream_iterator<kabalin::Polygon>(in),
              std::istream_iterator<kabalin::Polygon>(),
              std::back_inserter(polygons));
    if (in.fail()) {
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::map<std::string, std::function<void(const std::vector<kabalin::Polygon>,
                                           std::istream &, std::ostream &)>>
      commands{{"AREA", area_command},
               {"MAX", max_command},
               {"MIN", min_command},
               {"COUNT", count_command},
               {"LESSAREA", less_area_command},
               {"SAME", same_area_command}};

  std::cout << std::fixed;
  while (!std::cin.eof()) {
    try {
      std::string key;
      std::cin >> key;
      if (commands.find(key) != commands.end()) {
        auto command = std::bind(commands[key], std::placeholders::_1,
                                 std::placeholders::_2, std::placeholders::_3);
        command(polygons, std::cin, std::cout);
      } else if (!std::cin.eof()) {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    } catch (const std::exception &ex) {
      std::cout << ex.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}

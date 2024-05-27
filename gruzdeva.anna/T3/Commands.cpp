#include "Commands.hpp"

#include <algorithm>
#include <numeric>

bool isNumber(const std::string& s)
{
  return !s.empty() && std::find_if(s.begin(),
                                    s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

namespace commands {
  std::ostream& getArea(const std::vector<shapes::Polygon>& polygons, std::istream& is, std::ostream& os) {
    std::string specifier;
    is >> specifier;

    if (specifier == "EVEN") {
      os << getEvenAreaSum(polygons) << "\n";
    } else if (specifier == "ODD") {
      os << getOddAreaSum(polygons) << "\n";
    } else if (specifier == "MEAN") {
      os << getMeanArea(polygons) << "\n";
    } else if (isNumber(specifier)){
      std::size_t vertsNum = std::stoi(specifier);
      if (vertsNum < 3) {
        throw std::logic_error("<INCORRECT NUMBER OF VERTEXES>");
      }
      os << getAreaOfVertsNum(polygons, vertsNum) << "\n";
    } else {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    return os;
  }

  double getEvenAreaSum(const std::vector<shapes::Polygon>& polygons) {
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                 [](double currentSum, const shapes::Polygon& poly)
                                 {return currentSum + ((poly.points.size() % 2 == 0) ? shapes::getShapeArea(poly) : 0.0);
                                 });
    return sum;
  }

  double getOddAreaSum(const std::vector<shapes::Polygon>& polygons) {
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                 [](double currentSum, const shapes::Polygon& poly)
                                 {return currentSum + ((poly.points.size() % 2 != 0) ? shapes::getShapeArea(poly) : 0.0);
                                 });
    return sum;
  }

  double getMeanArea(const std::vector<shapes::Polygon>& polygons) {
    if (polygons.empty()) {
      throw std::logic_error("<EMPTY POLYGON LIST>");
    }

    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                 [](double currentSum, const shapes::Polygon& poly)
                                 {return currentSum + shapes::getShapeArea(poly);
                                 });
    return sum / polygons.size();
  }

  double getAreaOfVertsNum(const std::vector<shapes::Polygon>& polygons, std::size_t vertsNum) {
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                 [vertsNum](double currentSum, const shapes::Polygon& poly)
                                 {return currentSum + ((poly.points.size() == vertsNum) ? shapes::getShapeArea(poly) : 0.0);
                                 });
    return sum;
  }


  std::ostream& getMax(const std::vector<shapes::Polygon>& polygons, std::istream& is, std::ostream& os) {
    std::string specifier;
    is >> specifier;

    if (specifier == "AREA") {
      os << getMaxArea(polygons) << "\n";
    } else if (specifier == "VERTS") {
      os << getMaxVerts(polygons) << "\n";
    } else {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    return os;
  }

  double getMaxArea(const std::vector<shapes::Polygon>& polygons) {
    if (polygons.empty()) {
      throw std::logic_error("<EMPTY POLYGON LIST>");
    }

    std::vector<double> areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(),
                   [](const shapes::Polygon& poly) {return shapes::getShapeArea(poly);
                   });
    double maxArea = *std::max_element(areas.begin(), areas.end());
    return maxArea;
  }

  std::size_t getMaxVerts(const std::vector<shapes::Polygon>& polygons) {
    if (polygons.empty()) {
      throw std::logic_error("<EMPTY POLYGON LIST>");
    }

    std::vector<double> vertsNums(polygons.size());
    std::transform(polygons.begin(), polygons.end(), vertsNums.begin(),
                   [](const shapes::Polygon& poly) {return poly.points.size();
                   });
    std::size_t maxVerts = *std::max_element(vertsNums.begin(), vertsNums.end());
    return maxVerts;
  }


  std::ostream& getMin(const std::vector<shapes::Polygon>& polygons, std::istream& is, std::ostream& os) {
    std::string specifier;
    is >> specifier;

    if (specifier == "AREA") {
      os << getMinArea(polygons) << "\n";
    } else if (specifier == "VERTS") {
      os << getMinVerts(polygons) << "\n";
    } else {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    return os;
  }

  double getMinArea(const std::vector<shapes::Polygon>& polygons) {
    if (polygons.empty()) {
      throw std::logic_error("<EMPTY POLYGON LIST>");
    }

    std::vector<double> areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(),
                   [](const shapes::Polygon& poly) {return shapes::getShapeArea(poly);
                   });
    double minArea = *std::min_element(areas.begin(), areas.end());
    return minArea;
  }

  std::size_t getMinVerts(const std::vector<shapes::Polygon>& polygons) {
    if (polygons.empty()) {
      throw std::logic_error("<EMPTY POLYGON LIST>");
    }

    std::vector<double> vertsNums(polygons.size());
    std::transform(polygons.begin(), polygons.end(), vertsNums.begin(),
                   [](const shapes::Polygon& poly) {return poly.points.size();
                   });
    std::size_t minVerts = *std::min_element(vertsNums.begin(), vertsNums.end());
    return minVerts;
  }


  std::ostream& countShapes(const std::vector<shapes::Polygon>& polygons, std::istream& is, std::ostream& os) {
    std::string specifier;
    is >> specifier;

    if (specifier == "EVEN") {
      os << countEvenVerts(polygons) << "\n";
    } else if (specifier == "ODD") {
      os << countOddVerts(polygons) << "\n";
    } else if (isNumber(specifier)){
      std::size_t vertsNum = std::stoi(specifier);
      if (vertsNum < 3) {
        throw std::logic_error("<INCORRECT NUMBER OF VERTEXES>");
      }
      os << countShapesOfVertsNum(polygons, vertsNum) << "\n";
    } else {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    return os;
  }

  std::size_t countEvenVerts(const std::vector<shapes::Polygon>& polygons) {
    std::size_t count = std::count_if(polygons.begin(), polygons.end(),
                                      [](const shapes::Polygon& poly) {return poly.points.size() % 2 == 0;
                                      });
    return count;
  }

  std::size_t countOddVerts(const std::vector<shapes::Polygon>& polygons) {
    std::size_t count = std::count_if(polygons.begin(), polygons.end(),
                                      [](const shapes::Polygon& poly) {return poly.points.size() % 2 != 0;
                                      });
    return count;
  }

  std::size_t countShapesOfVertsNum(const std::vector<shapes::Polygon>& polygons, std::size_t vertsNum) {
    std::size_t count = std::count_if(polygons.begin(), polygons.end(),
                                      [vertsNum](const shapes::Polygon& poly) {return poly.points.size() == vertsNum;
                                      });
    return count;
  }
}

#include "Commands.hpp"

#include <algorithm>
#include <numeric>
#include <iterator>
#include <iomanip>

bool isNumber(const std::string& s)
{
  return !s.empty() && std::find_if(s.begin(),
                                    s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

namespace commands {
  std::ostream& getArea(const std::vector<shapes::Polygon>& polygons, std::istream& is, std::ostream& os) {
    std::string specifier;
    is >> specifier;

    os << std::setprecision(1) << std::fixed;
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
    } else if (specifier == "VERTEXES") {
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
    } else if (specifier == "VERTEXES") {
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


  std::ostream& echo(std::vector<shapes::Polygon>& polygons, std::istream& is, std::ostream& os) {
    if (polygons.empty()) {
      throw std::logic_error("<EMPTY POLYGON LIST>");
    }

    shapes::Polygon requiredPolygon;
    if (!(is >> requiredPolygon)) {
      throw std::invalid_argument("<INVALID POLYGON>");
    }

    int inserted = createDuplicates(requiredPolygon, polygons);

    os << inserted << "\n";
    return os;
  }

  int createDuplicates(const shapes::Polygon& requiredPolygon, std::vector<shapes::Polygon>& polygons) {
    std::vector<std::size_t> indexes;
    int ind = 0;
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(indexes),
                   [&requiredPolygon, &ind](const shapes::Polygon& poly) {
                    if (poly == requiredPolygon) {
                      return ind++;
                    } else {
                      ++ind;
                      return -1;
                    }
                   });
    indexes.erase(std::remove(indexes.begin(), indexes.end(), -1), indexes.end());

    int inserted = 0;
    std::vector<int> dummy;
    std::transform(indexes.begin(), indexes.end(), std::back_inserter(dummy),
                   [&polygons, &requiredPolygon, &inserted](std::size_t index) {
                       polygons.insert(polygons.begin() + index + inserted, requiredPolygon);
                        ++inserted;
                       return 0; // return value is not used
                   });
    return inserted;
  }


  std::ostream& inFrame(const std::vector<shapes::Polygon>& polygons, std::istream& is, std::ostream& os) {
    if (polygons.empty()) {
      throw std::logic_error("<EMPTY POLYGON LIST>");
    }

    shapes::Polygon poly;
    if (!(is >> poly)) {
      throw std::invalid_argument("<INVALID POLYGON>");
    }

    shapes::Polygon frame = getFrame(polygons);
    bool inFrame = std::all_of(poly.points.cbegin(), poly.points.cend(),
                               [&frame](const shapes::Point& point) {
                                 return point.x >= frame.points[0].x && point.x <= frame.points[2].x &&
                                        point.y >= frame.points[0].y && point.y <= frame.points[2].y;
                               });

    if (inFrame) {
      os << "<TRUE>\n";
    }
    else {
      os << "<FALSE>\n";
    }

    return  os;
  }

  shapes::Polygon getFrame(const std::vector<shapes::Polygon>& polygons) {
    std::vector<int> vecMaxX(polygons.size());
    std::transform(
        polygons.begin(),
        polygons.end(),
        vecMaxX.begin(),
        getMaxX
    );
    int maxX = *(std::max_element(vecMaxX.cbegin(), vecMaxX.cend()));

    std::vector<int> vecMaxY(polygons.size());
    std::transform(
        polygons.begin(),
        polygons.end(),
        vecMaxY.begin(),
        getMaxY
    );
    int maxY = *(std::max_element(vecMaxY.cbegin(), vecMaxY.cend()));

    std::vector<int> vecMinX(polygons.size());
    std::transform(
        polygons.begin(),
        polygons.end(),
        vecMinX.begin(),
        getMinX
    );
    int minX = *(std::min_element(vecMinX.cbegin(), vecMinX.cend()));

    std::vector<int> vecMinY(polygons.size());
    std::transform(
        polygons.begin(),
        polygons.end(),
        vecMinY.begin(),
        getMinY
    );
    int minY = *(std::min_element(vecMinY.cbegin(), vecMinY.cend()));

    shapes::Polygon frame = {
        {
            {minX, minY},
            {maxX, minY},
            {maxX, maxY},
            {minX, maxY}
        }
    };

    return frame;
  }

  int getMaxX(const shapes::Polygon& shape) {
    std::vector< int > vecPointX(shape.points.size());
    std::transform(
        shape.points.cbegin(),
        shape.points.cend(),
        vecPointX.begin(),
        shapes::getX
    );
    int maxPointX = *(std::max_element(vecPointX.cbegin(), vecPointX.cend()));
    return maxPointX;
  }

  int getMaxY(const shapes::Polygon& shape) {
    std::vector< int > vecPointY(shape.points.size());
    std::transform(
        shape.points.cbegin(),
        shape.points.cend(),
        vecPointY.begin(),
        shapes::getY
    );
    int maxPointY = *(std::max_element(vecPointY.cbegin(), vecPointY.cend()));
    return maxPointY;
  }

  int getMinX(const shapes::Polygon& shape) {
    std::vector< int > vecPointX(shape.points.size());
    std::transform(
        shape.points.cbegin(),
        shape.points.cend(),
        vecPointX.begin(),
        shapes::getX
    );
    int minPointX = *(std::min_element(vecPointX.cbegin(), vecPointX.cend()));
    return minPointX;
  }

  int getMinY(const shapes::Polygon& shape) {
    std::vector< int > vecPointY(shape.points.size());
    std::transform(
        shape.points.cbegin(),
        shape.points.cend(),
        vecPointY.begin(),
        shapes::getY
    );
    int minPointY = *(std::min_element(vecPointY.cbegin(), vecPointY.cend()));
    return minPointY;
  }

  std::ostream& outError(std::ostream& os, const std::string& message) {
    os << message << "\n";
    return os;
  }
}

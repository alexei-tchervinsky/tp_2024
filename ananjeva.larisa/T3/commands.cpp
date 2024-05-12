#include "commands.hpp"
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <iomanip>
#include <numeric>

std::ostream& ananjeva::getAreas(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out) {
  if (shapes.empty()) {
    throw std::logic_error("No one shape, cannot continue.");
  }
  std::string areaType = "";
  in >> areaType;
  out << std::fixed << std::setprecision(1);
  if (areaType == "EVEN") {
    out << getEvenAreas(shapes) << '\n';
  }
  else if (areaType == "ODD") {
    out << getOddAreas(shapes) << '\n';
  }
  else if (areaType == "MEAN") {
    out << getMeanArea(shapes) << '\n';
  }
  else {

    //auto is_digit = std::bind(std::isdigit, std::placeholders::_1);
    //auto is_digit = std::bind(static_cast<int(*)(char)>(std::isdigit), std::placeholders::_1);
    //if (std::count_if(std::begin(areaType), std::end(areaType), static_cast<int(*)(int)>(std::isdigit)))
    if (std::count_if(std::begin(areaType), std::end(areaType), [](unsigned char value) { return std::isdigit(value); }) ==
    areaType.size()) {
      std::size_t vertsNum = std::stoi(areaType);
      if (vertsNum <= 2) {
        throw std::logic_error("Incorrect verts number ");
      }
      out << getAreasOfVertsNum(shapes, vertsNum) << '\n';
    }
    else {
      throw std::logic_error("<INVALID COMMAND");
    }
  }
  return out;
}

double ananjeva::getEvenAreas(const std::vector< Polygon >& shapes) {
  return std::accumulate(shapes.cbegin(), shapes.cend(), 0, sumEvenAreas);
}

double ananjeva::getOddAreas(const std::vector< Polygon >& shapes) {
  return std::accumulate(shapes.cbegin(), shapes.cend(), 0, sumOddAreas);
}

double ananjeva::getMeanArea(const std::vector< Polygon >& shapes) {
  if (shapes.empty()) {
    throw std::logic_error("No one shape, cannot find mean area.");
  }
  double areas = std::accumulate(shapes.cbegin(), shapes.cend(), 0, sumAreas);
  double meanArea = areas / shapes.size();
  return meanArea;
}

double ananjeva::getAreasOfVertsNum(const std::vector< Polygon >& shapes, std::size_t vertsNum) {
  return std::accumulate(
    shapes.cbegin(),
    shapes.cend(),
    0,
    std::bind(sumEqualAreas, std::placeholders::_1, std::placeholders::_2, vertsNum)
  );
}

std::ostream& ananjeva::getMax(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out) {
  if (shapes.empty()) {
    throw std::logic_error("No one shape, cannot continue.");
  }
  std::string option = "";
  in >> option;
  if (option == "AREA") {
    out << std::fixed << std::setprecision(1) << getMaxArea(shapes) << '\n';
  }
  else if (option == "VERTEXES") {
    out << getMaxVerts(shapes) << '\n';
  }
  else {
    throw std::logic_error("<INVALID COMMAND>");
  }
  return out;
}

double ananjeva::getMaxArea(const std::vector< Polygon >& shapes) {
  std::vector< double > vecOfAreas(shapes.size());
  std::transform(
    shapes.cbegin(),
    shapes.cend(),
    vecOfAreas.begin(),
    getShapeArea
  );
  double maxArea = *(std::max_element(vecOfAreas.cbegin(), vecOfAreas.cend()));
  return maxArea;
}


double ananjeva::getMaxVerts(const std::vector< Polygon >& shapes) {
  std::vector< double > vecOfVertsNum(shapes.size());
  std::transform(
    shapes.cbegin(),
    shapes.cend(),
    vecOfVertsNum.begin(),
    getVertsNum
  );
  std::size_t maxVertsNum = *(std::max_element(vecOfVertsNum.cbegin(), vecOfVertsNum.cend()));
  return maxVertsNum;
}

std::ostream& ananjeva::getMin(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out) {
    if (shapes.empty()) {
    throw std::logic_error("No one shape, cannot continue.");
  }
  std::string option = "";
  in >> option;
  if (option == "AREA") {
    out << std::fixed << std::setprecision(1) << getMinArea(shapes) << '\n';
  }
  else if (option == "VERTEXES") {
    out << getMinVerts(shapes) << '\n';
  }
  else {
    throw std::logic_error("<INVALID COMMAND>");
  }
  return out;
}

double ananjeva::getMinArea(const std::vector< Polygon >& shapes) {
  std::vector< double > vecOfAreas(shapes.size());
  std::transform(
    shapes.cbegin(),
    shapes.cend(),
    vecOfAreas.begin(),
    getShapeArea
  );
  double minArea = *(std::min_element(vecOfAreas.cbegin(), vecOfAreas.cend()));
  return minArea;
}

double ananjeva::getMinVerts(const std::vector< Polygon >& shapes) {
  std::vector< double > vecOfVertsNum(shapes.size());
  std::transform(
    shapes.cbegin(),
    shapes.cend(),
    vecOfVertsNum.begin(),
    getVertsNum
  );
  std::size_t minVertsNum = *(std::min_element(vecOfVertsNum.cbegin(), vecOfVertsNum.cend()));
  return minVertsNum;
}

std::ostream& ananjeva::countShapes(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out) {
  if (shapes.empty()) {
    throw std::logic_error("No one shape, cannot continue.");
  }
  std::string vertsType = "";
  in >> vertsType;
  if (vertsType == "EVEN") {
    out << countWithEvenVerts(shapes) << '\n';
  }
  else if (vertsType == "ODD") {
    out << countWithOddVerts(shapes) << '\n';
  }
  else {
    if (std::count_if(std::begin(vertsType), std::end(vertsType), [](unsigned char value) { return std::isdigit(value); }) ==
    vertsType.size()) {
      std::size_t vertsNum = std::stoi(vertsType);
      if (vertsNum <= 2) {
        throw std::logic_error("Incorrect verts number.");
      }
      out << countWithNumOfVerts(shapes, vertsNum) << '\n';
    }
    else {
      throw std::logic_error("<INVALID COMMAND");
    }
  }
  return out;
}

std::size_t ananjeva::countWithEvenVerts(const std::vector< Polygon >& shapes) {
  return std::count_if(shapes.cbegin(), shapes.cend(), isVertsNumEven);
}

std::size_t ananjeva::countWithOddVerts(const std::vector< Polygon >& shapes) {
  return std::count_if(shapes.cbegin(), shapes.cend(), isVertsNumOdd);
}

std::size_t ananjeva::countWithNumOfVerts(const std::vector< Polygon >& shapes, std::size_t vertsNum) {
  return std::count_if(shapes.cbegin(), shapes.cend(), std::bind(isVertsNumRequired, std::placeholders::_1, vertsNum));
}

std::ostream& ananjeva::countRmSimilarShapes(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out) {

}

std::ostream& ananjeva::checkInFrame(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out) {

}

std::ostream& ananjeva::outError(std::ostream& out, const std::string& errorMessage) {
  out << errorMessage << '\n';
  return out;
}

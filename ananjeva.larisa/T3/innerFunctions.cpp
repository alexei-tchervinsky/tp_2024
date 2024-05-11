#include "innerFunctions.hpp"
#include <algorithm>
#include <numeric>

int ananjeva::getDiffOfMultCoords(const Point& point1, const Point& point2) {
  return point1.x * point2.y - point1.y * point2.x;
}

double ananjeva::getShapeArea(const Polygon& shape) {
  std::vector< int > diffOfCoords(shape.points.size());
  std::transform(
    ++shape.points.cbegin(),
    shape.points.cend(),
    shape.points.cbegin(),
    diffOfCoords.cbegin(),
    getDiffOfMultCoords //std::bind(getDiffOfMultCoords, _1, _2)
  );
  diffOfCoords.push_back(getDiffOfMultCoords(shape.points.front(), shape.points.back()));
  int area = std::accumulate(diffOfCoords.cbegin(), diffOfCoords.cend(), 0);
  double res = abs(area) / 2.0;
  return res;
}

double ananjeva::sumEvenAreas(const Polygon& shape, double sum) {
  if (shape.points.size() % 2 == 0) {
    return sum + getShapeArea(shape);
  }
  else {
    return sum;
  }
}

double ananjeva::sumOddAreas(const Polygon& shape, double sum) {
    if (shape.points.size() % 2 != 0) {
    return sum + getShapeArea(shape);
  }
  else {
    return sum;
  }
}

double ananjeva::sumAreas(const Polygon& shape, double sum) {
    return sum + getShapeArea(shape);
}

double ananjeva::sumEqualAreas(const Polygon& shape, std::size_t vertsNum, double sum) {
    if (shape.points.size() == vertsNum) {
    return sum + getShapeArea(shape);
  }
  else {
    return sum;
  }
}

std::size_t ananjeva::getVertsNum(const Polygon& shape) {
  return shape.points.size();
}

bool ananjeva::isVertsNumEven(const Polygon& shape) {
  return shape.points.size() % 2 == 0;
}

bool ananjeva::isVertsNumOdd(const Polygon& shape) {
  return shape.points.size() % 2 != 0;
}

bool ananjeva::isVertsNumRequired(const Polygon& shape, std::size_t vertsNum) {
  return (shape.points.size() == vertsNum);
}
#include "innerFunctions.hpp"
#include <algorithm>
#include <functional>
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
    diffOfCoords.begin(),
    getDiffOfMultCoords
  );
  diffOfCoords.push_back(getDiffOfMultCoords(shape.points.front(), shape.points.back()));
  int area = std::accumulate(diffOfCoords.cbegin(), diffOfCoords.cend(), 0.0);
  double res = abs(area) / 2.0;
  return res;
}

double ananjeva::sumEvenAreas(double sum, const Polygon& shape) {
  if (shape.points.size() % 2 == 0) {
    return sum + getShapeArea(shape);
  }
  else {
    return sum;
  }
}

double ananjeva::sumOddAreas(double sum, const Polygon& shape) {
    if (shape.points.size() % 2 != 0) {
    return sum + getShapeArea(shape);
  }
  else {
    return sum;
  }
}

double ananjeva::sumAreas(double sum, const Polygon& shape) {
    return sum + getShapeArea(shape);
}

double ananjeva::sumEqualAreas(double sum, const Polygon& shape, std::size_t vertsNum) {
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

bool ananjeva::SamePolygonSeries::operator()(const Polygon& polygon, const Polygon& requiredPolygon) {
  if (polygon == requiredPolygon) {
    if (++series_ > 1) {
      return true;
    }
  }
  else {
    series_ = 0;
  }
  return false;
}

std::size_t ananjeva::getCountOfRmShapes(std::vector< Polygon >& shapes, const Polygon& requiredPolygon) {
  std::vector< std::size_t > vecOfSamePolygons(shapes.size());
  SamePolygonSeries series;
  std::size_t counterOfRmPolygons = std::count_if(
    shapes.begin(),
    shapes.end(),
    std::bind(series, std::placeholders::_1, requiredPolygon)
  );
  std::remove_if(
    shapes.begin(),
    shapes.end(),
    std::bind(series, std::placeholders::_1, requiredPolygon)
  );

  return counterOfRmPolygons;
}

int ananjeva::getX(const Point& point) {
  return point.x;
}

int ananjeva::getY(const Point& point) {
  return point.y;
}

int ananjeva::getMaxX(const Polygon& shape) {
  std::vector< int > vecPointX(shape.points.size());
  std::transform(
    shape.points.cbegin(),
    shape.points.cend(),
    vecPointX.begin(),
    getX
  );
  int maxPointX = *(std::max_element(vecPointX.cbegin(), vecPointX.cend()));
  return maxPointX;
}

int ananjeva::getMaxY(const Polygon& shape) {
  std::vector< int > vecPointY(shape.points.size());
  std::transform(
    shape.points.cbegin(),
    shape.points.cend(),
    vecPointY.begin(),
    getY
  );
  int maxPointY = *(std::max_element(vecPointY.cbegin(), vecPointY.cend()));
  return maxPointY;
}

int ananjeva::getMinX(const Polygon& shape) {
  std::vector< int > vecPointX(shape.points.size());
  std::transform(
    shape.points.cbegin(),
    shape.points.cend(),
    vecPointX.begin(),
    getX
  );
  int minPointX = *(std::min_element(vecPointX.cbegin(), vecPointX.cend()));
  return minPointX;
}

int ananjeva::getMinY(const Polygon& shape) {
  std::vector< int > vecPointY(shape.points.size());
  std::transform(
    shape.points.cbegin(),
    shape.points.cend(),
    vecPointY.begin(),
    getY
  );
  int minPointY = *(std::min_element(vecPointY.cbegin(), vecPointY.cend()));
  return minPointY;
}

ananjeva::Polygon ananjeva::getFrame(const std::vector< Polygon >& shapes) {
  std::vector< int > vecMaxX(shapes.size());
  std::transform(
    shapes.cbegin(),
    shapes.cend(),
    vecMaxX.begin(),
    getMaxX
  );
  int maxX = *(std::max_element(vecMaxX.cbegin(), vecMaxX.cend()));

  std::vector< int > vecMaxY(shapes.size());
  std::transform(
    shapes.cbegin(),
    shapes.cend(),
    vecMaxY.begin(),
    getMaxY
  );
  int maxY = *(std::max_element(vecMaxY.cbegin(), vecMaxY.cend()));

  std::vector< int > vecMinX(shapes.size());
  std::transform(
    shapes.cbegin(),
    shapes.cend(),
    vecMinX.begin(),
    getMinX
  );
  int minX = *(std::min_element(vecMinX.cbegin(), vecMinX.cend()));

  std::vector< int > vecMinY(shapes.size());
  std::transform(
    shapes.cbegin(),
    shapes.cend(),
    vecMinY.begin(),
    getMinY
  );
  int minY = *(std::min_element(vecMinY.cbegin(), vecMinY.cend()));

  Polygon frame{};
  Point rightUp = { maxX, maxY };
  Point leftDown = { minX, minY };
  frame.points.push_back(leftDown);
  frame.points.push_back(rightUp);
  return frame;
}

bool ananjeva::isPolygonInFrame(const Polygon& frame, const Polygon& testingPolygon) {
  int testPolyMaxX = getMaxX(testingPolygon);
  int testPolyMaxY = getMaxY(testingPolygon);
  int testPolyMinX = getMinX(testingPolygon);
  int testPolyMinY = getMinY(testingPolygon);
  if ((testPolyMinX >= frame.points[0].x) &&
    (testPolyMinY >= frame.points[0].y) &&
    (testPolyMaxX <= frame.points[1].x) &&
    (testPolyMaxY <= frame.points[1].y))
  {
    return true;
  }
  else {
    return false;
  }
}

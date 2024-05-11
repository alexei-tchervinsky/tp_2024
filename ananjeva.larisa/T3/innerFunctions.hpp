#ifndef INNER_FUNCTIONS_HPP
#define INNER_FUNCTIONS_HPP
#include "polygon.hpp"

namespace ananjeva {
  int getDiffOfMultCoords(const Point& point1, const Point& point2);
  double getShapeArea(const Polygon& shape);
  double sumEvenAreas(const Polygon& shape, double sum);
  double sumOddAreas(const Polygon& shape, double sum);
  double sumAreas(const Polygon& shape, double sum);
  double sumEqualAreas(const Polygon& shape, std::size_t vertsNum, double sum);

  std::size_t getVertsNum(const Polygon& shape);
  bool isVertsNumEven(const Polygon& shape);
  bool isVertsNumOdd(const Polygon& shape);
  bool isVertsNumRequired(const Polygon& shape, std::size_t vertsNum);

}

#endif

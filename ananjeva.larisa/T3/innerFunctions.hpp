#ifndef INNER_FUNCTIONS_HPP
#define INNER_FUNCTIONS_HPP
#include "polygon.hpp"

namespace ananjeva {
  struct SamePolygonSeries {
  public:
    bool operator()(const Polygon& polygon, const Polygon& requiredPolygon);
    std::size_t counterOfRmPolygons = 0;
  private:
    std::size_t series_ = 0;
  };

  std::size_t getCountOfRmShapes(std::vector< Polygon >& shapes, const Polygon& requiredPolygon);

  int getDiffOfMultCoords(const Point& point1, const Point& point2);
  double getShapeArea(const Polygon& shape);
  double sumEvenAreas(double sum, const Polygon& shape);
  double sumOddAreas(double sum, const Polygon& shape);
  double sumAreas(double sum, const Polygon& shape);
  double sumEqualAreas(double sum, const Polygon& shape, std::size_t vertsNum);

  std::size_t getVertsNum(const Polygon& shape);
  bool isVertsNumEven(const Polygon& shape);
  bool isVertsNumOdd(const Polygon& shape);
  bool isVertsNumRequired(const Polygon& shape, std::size_t vertsNum);

  int getX(const Point& point);
  int getY(const Point& point);
  int getMaxX(const Polygon& shape);
  int getMaxY(const Polygon& shape);
  int getMinX(const Polygon& shape);
  int getMinY(const Polygon& shape);
  Polygon getFrame(const std::vector< Polygon >& shapes);
  bool isPolygonInFrame(const Polygon& frame, const Polygon& testingPolygon);
}

#endif

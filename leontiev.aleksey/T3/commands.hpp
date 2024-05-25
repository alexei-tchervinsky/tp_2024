#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "geometryShapes.hpp"

namespace leontiev
{
  std::ostream& calculateArea(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  double calculateEvenArea(const std::vector<Polygon>& polygons);
  double calculateOddArea(const std::vector<Polygon>& polygons);
  double oddAreasSum(double result, const Polygon& polygon);
  double evenAreasSum(double result, const Polygon& polygon);
  double equalAreasSum(double result, const Polygon& polygon, std::size_t vertexNum);
  double areasSum(double result, const Polygon& polygon);
  double areaCount(const Polygon& polygon);
  int pairDifference(const Point& first, const Point& second);
  double calculateMeanArea(const std::vector<Polygon>& polygons);
  double calculateVertexes(const std::vector<Polygon>& polygons, int vertexNum);

  std::ostream& getMax(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  double getMaxArea(const std::vector<Polygon>& polygons);
  double getMaxVertexes(const std::vector<Polygon>& polygons);
  int vertexCount(const Polygon& polygon);

  std::ostream& getMin(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  double getMinArea(const std::vector<Polygon>& polygons);
  double getMinVertexes(const std::vector<Polygon>& polygons);

  std::ostream& count(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  int evenCount(const std::vector<Polygon>& polygons);
  bool isVertexEven(const Polygon polygon);
  int oddCount(const std::vector<Polygon>& polygons);
  bool isVertexOdd(const Polygon polygon);
  int shapeCount(const std::vector<Polygon>& polygons, int vertexNum);
  bool isVertexEqual(const Polygon polygon, std::size_t vertexNum);

  int getMaxCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point));
  int getMinCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point));

  int getX(const Point& point);
  int getY(const Point& point);
  std::vector<Point> getFrame(const std::vector<Polygon>& polygons);
  std::ostream& inFrame(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  bool isInFrame(const std::vector<Polygon>& polygons, const Polygon& polygon);

  std::ostream& maxSeq(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  bool isEqualPolygons(const Polygon& first, const Polygon& second);
  bool isEquaPoints(const Point& first, const Point& second);
}

#endif

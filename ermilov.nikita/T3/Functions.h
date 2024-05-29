#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <iostream>
#include "Geometry.h"

namespace ermilov
{
  //functions
  double getArea(const Polygon& polygon);
  int getVertAmount(const Polygon& polygon);
  int getSubArea(const Point& first, const Point& second);

  double sumEven(double result, const Polygon& polygon);
  double sumOdd(double result, const Polygon& polygon);
  double sumNum(double result, const Polygon& polygon, size_t vertNum);
  double sumAll(double result, const Polygon& polygon);

  bool areIntersect(const Polygon& first, const Polygon& second);
  Point getMaxPoint(const Polygon& polygon);
  Point getMinPoint(const Polygon& polygon);

  void errorMessage(std::ostream& out, const std::string& message);

  //commands
  std::ostream& chooseCommand(std::istream& in, std::ostream& out, std::vector<Polygon>& polygons);

  double areaEven(const std::vector<Polygon>& polygons);
  double areaOdd(const std::vector<Polygon>& polygons);
  double areaMean(const std::vector<Polygon>& polygons);
  double areaNum(int vertNum, const std::vector<Polygon>& polygons);

  double maxArea(const std::vector<Polygon>& polygons);
  double maxVert(const std::vector<Polygon>& polygons);
  double minArea(const std::vector<Polygon>& polygons);
  double minVert(const std::vector<Polygon>& polygons);

  double countEven(const std::vector<Polygon>& polygons);
  double countOdd(const std::vector<Polygon>& polygons);
  double countNum(size_t vertNum, const std::vector<Polygon>& polygons);

  int rmecho(std::vector<Polygon>& polygons, std::istream& in);
  int intersections(const std::vector<Polygon>& polygons, std::istream& in);
}

#endif // !FUNCTIONS_H

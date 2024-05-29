#ifndef COMMANDS_H
#define COMMANDS_H

#include "polygon.h"
#include <functional>
#include <string>

namespace bekhova
{
  void Area(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  void AreaEven(const std::vector<Polygon>& polygons, std::ostream& out);
  void AreaOdd(const std::vector<Polygon>& polygons, std::ostream& out);
  void AreaMean(const std::vector<Polygon>& polygons, std::ostream& out);
  void AreaVersNum(std::size_t vertexes, const std::vector<Polygon>& polygons, std::ostream& out);
  double sumAreas(const std::vector<Polygon>& polygons);
  double getArea(const Polygon& polygon);

  void Max(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  void maxArea(const std::vector<Polygon>& polygons, std::ostream& out);
  void maxVertexes(const std::vector<Polygon>& polygons, std::ostream& out);

  void Min(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  void minArea(const std::vector<Polygon>& polygons, std::ostream& out);
  void minVertexes(const std::vector<Polygon>& polygons, std::ostream& out);

  void Count(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  void CountEven(const std::vector<Polygon>& polygons, std::ostream& out);
  void CountOdd(const std::vector<Polygon>& polygons, std::ostream& out);
  void CountVertexes(std::size_t vertexes, const std::vector<Polygon>& polygons, std::ostream& out);

  void Perms(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
  bool checkPerms(const Polygon& left, const Polygon& right);
  bool checkPoints(const Polygon& polygon, const Point& point);

  void Rightshapes(const std::vector<Polygon>& polygons, std::ostream& out);
  bool isRightAngle(const Polygon& polygon);
  Point vectorOnCoords(const Point& firstPoint, const Point& secondPoint);
  double cosFromVects(const Point& firstPoint, const Point& secondPoint);

  void outMessage(std::ostream& out, const std::string& message);
}
#endif
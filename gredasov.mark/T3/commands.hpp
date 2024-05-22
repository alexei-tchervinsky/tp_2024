#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include <vector>

#include "polygon.hpp"

namespace gredasov
{
  void getAreaCommand(const std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);
  double addArea(double accumulator, const Polygon& polygon);
  double addEvenArea(double accumulator, const Polygon& polygon);
  double addOddArea(double accumulator, const Polygon& polygon);
  double sumOfAreas(const std::vector< Polygon >& polygons);
  double sumOfEvenAreas(const std::vector<Polygon>& polygons);
  double sumOfOddAreas(const std::vector<Polygon>& polygons);
  double sumOfMeanAreas(const std::vector<Polygon>& polygons);
  double sumOfNumAreas(const std::vector<Polygon>& polygons, std::size_t num);
  double getArea(const Polygon& polygon);

  void getMaxCommand(const std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);
  double getMinMaxArea(const std::vector< Polygon >& polygons, std::size_t& parameter);
  std::size_t getMinMaxVertexes(const std::vector< Polygon >& polygons, std::size_t& parameter);
  void getMinCommand(const std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);

  void getCountCommand(const std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);
  std::size_t getCountOfEven(const std::vector< Polygon >& polygons);
  std::size_t getCountOfOdd(const std::vector< Polygon >& polygons);
  std::size_t getCountOfNum(const std::vector< Polygon >& polygons, std::size_t num);

  void isInFrameCommand(const std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);
  int getMinMaxX(const Polygon& polygon, std::size_t parameter);
  int getMinMaxY(const Polygon& polygon, std::size_t parameter);
  Polygon getFrame(const std::vector< Polygon >& polygons);
  bool isInFrame(const std::vector< Polygon >& polygons, const Polygon& polygon);

  void getIntersectionsCommand(const std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);
  bool isPointInPolygon(const Polygon& polygon, const Point& point);
  bool areTwoPolygonsIntersected(const Polygon& p1, const Polygon& p2);

  void outputMessage(std::ostream& out, std::size_t message);
  void outputMessage(std::ostream& out, double message);
  void outputMessage(std::ostream& out, std::string message);
}

#endif


#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Polygon.hpp"
#include <string>
#include <functional>

namespace semzin
{
  void Area(std::vector<Polygon> &polygons, std::ostream &out, std::istream &in);
  void AreaEven(std::vector<Polygon> &polygons, std::ostream &out);
  void AreaOdd(std::vector<Polygon> &polygons, std::ostream &out);
  void AreaMean(std::vector<Polygon> &polygons, std::ostream &out);
  void AreaVersNum(std::size_t vertexes, std::vector<Polygon> &polygons, std::ostream &out);
  double sumAreas(std::vector<Polygon> &polygons);
  double getArea(const Polygon &polygon);

  void Max(std::vector<Polygon> &polygons, std::ostream &out, std::istream &in);
  void maxArea(std::vector<Polygon> &polygons, std::ostream &out);
  void maxVertexes(std::vector<Polygon> &polygons, std::ostream &out);

  void Min(std::vector<Polygon> &polygons, std::ostream &out, std::istream &in);
  void minArea(std::vector<Polygon> &polygons, std::ostream &out);
  void minVertexes(std::vector<Polygon> &polygons, std::ostream &out);

  void Count(std::vector<Polygon> &polygons, std::ostream &out, std::istream &in);
  void CountEven(std::vector<Polygon> &polygons, std::ostream &out);
  void CountOdd(std::vector<Polygon> &polygons, std::ostream &out);
  void CountVertexes(std::size_t vertexes, std::vector<Polygon> &polygons, std::ostream &out);

  void outMessage(std::ostream &out, const std::string &message);
}
#endif

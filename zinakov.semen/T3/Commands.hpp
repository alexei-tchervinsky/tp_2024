#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Polygon.hpp"

namespace semzin
{
  void Area(std::vector<Polygon> &polygon, std::ostream &out, std::istream &in);
  void AreaEven(std::vector<Polygon> &polygons, std::ostream &out);
  void AreaOdd(std::vector<Polygon> &polygons, std::ostream &out);
  void AreaMean(std::vector<Polygon> &polygons, std::ostream &out);
  void AreaVersNum(std::size_t vertexes, std::vector<Polygon> &polygons, std::ostream &out);
  double sumAreas(std::vector<Polygon> &polygons);
  double getArea(const Polygon &polygon);

  void outMessage(std::ostream &out, const std::string &message);
}
#endif

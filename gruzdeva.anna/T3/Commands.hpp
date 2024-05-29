#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>

#include "Polygon.hpp"

// var 5. ECHO & INFRAME

namespace commands {
  std::ostream& getArea(const std::vector<shapes::Polygon>& polygons, std::istream& is, std::ostream& os);
  double getEvenAreaSum(const std::vector<shapes::Polygon>& polygons);
  double getOddAreaSum(const std::vector<shapes::Polygon>& polygons);
  double getMeanArea(const std::vector<shapes::Polygon>& polygons);
  double getAreaOfVertsNum(const std::vector<shapes::Polygon>& polygons, std::size_t vertsNum);

  std::ostream& getMax(const std::vector<shapes::Polygon>& polygons, std::istream& is, std::ostream& os);
  double getMaxArea(const std::vector<shapes::Polygon>& polygons);
  std::size_t getMaxVerts(const std::vector<shapes::Polygon>& polygons);

  std::ostream& getMin(const std::vector<shapes::Polygon>& polygons, std::istream& is, std::ostream& os);
  double getMinArea(const std::vector<shapes::Polygon>& polygons);
  std::size_t getMinVerts(const std::vector<shapes::Polygon>& polygons);

  std::ostream& countShapes(const std::vector<shapes::Polygon>& polygons, std::istream& is, std::ostream& os);
  std::size_t countEvenVerts(const std::vector<shapes::Polygon>& polygons);
  std::size_t countOddVerts(const std::vector<shapes::Polygon>& polygons);
  std::size_t countShapesOfVertsNum(const std::vector<shapes::Polygon>& polygons, std::size_t vertsNum);

  std::ostream& echo(std::vector<shapes::Polygon>& polygons, std::istream& is, std::ostream& os);
  int createDuplicates(const shapes::Polygon& requiredPolygon, std::vector<shapes::Polygon>& polygons);

  std::ostream& inFrame(const std::vector<shapes::Polygon>& polygons, std::istream& is, std::ostream& os);
  shapes::Polygon getFrame(const std::vector<shapes::Polygon>& polygons);
  int getMaxX(const shapes::Polygon& poly);
  int getMaxY(const shapes::Polygon& poly);
  int getMinX(const shapes::Polygon& poly);
  int getMinY(const shapes::Polygon& poly);

  std::ostream& outError(std::ostream& os, const std::string& message);
}

#endif //COMMANDS_HPP

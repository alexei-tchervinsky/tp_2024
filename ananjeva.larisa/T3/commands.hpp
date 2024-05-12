#ifndef COMANDS_HPP
#define COMANDS_HPP
#include "innerFunctions.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace ananjeva {
  std::ostream& getAreas(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out);
  double getEvenAreas(const std::vector< Polygon >& shapes);
  double getOddAreas(const std::vector< Polygon >& shapes);
  double getMeanArea(const std::vector< Polygon >& shapes);
  double getAreasOfVertsNum(const std::vector< Polygon >& shapes, std::size_t vertsNum);

  std::ostream& getMax(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out);
  double getMaxArea(const std::vector< Polygon >& shapes);
  double getMaxVerts(const std::vector< Polygon >& shapes);

  std::ostream& getMin(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out);
  double getMinArea(const std::vector< Polygon >& shapes);
  double getMinVerts(const std::vector< Polygon >& shapes);

  std::ostream& countShapes(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out);
  std::size_t countWithEvenVerts(const std::vector< Polygon >& shapes);
  std::size_t countWithOddVerts(const std::vector< Polygon >& shapes);
  std::size_t countWithNumOfVerts(const std::vector< Polygon >& shapes, std::size_t vertsNum);

  std::ostream& countRmSimilarShapes(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out);
  std::ostream& checkInFrame(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out);

  std::ostream& outError(std::ostream& out, const std::string& errorMessage);
}

#endif

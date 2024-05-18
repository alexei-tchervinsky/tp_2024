#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "dataStruct.hpp"

namespace evstigneev
{
  std::ostream& area(std::istream& in, std::ostream& out, const std::vector<Polygon>& poly);
  std::ostream& max(std::istream& in, std::ostream& out, const std::vector<Polygon>& poly);
  std::ostream& min(std::istream& in, std::ostream& out, const std::vector<Polygon>& poly);
  std::ostream& count(std::istream& in, std::ostream& out, const std::vector<Polygon>& poly);
  std::ostream& lessArea(std::istream& in, std::ostream& out, const std::vector<Polygon>& poly);
  std::ostream& maxSeq(std::istream& in, std::ostream& out, const std::vector<Polygon>& poly);
  double countArea(const Polygon& poly);
  double sumAreaEven(double res, const Polygon& poly);
  double sumAreaOdd(double res, const Polygon& poly);
  double sumAreas(double res, const Polygon& poly);
  double sumAreaEqual(double res, const Polygon& poly, size_t numOfVexes);
  double countAreasEven(const std::vector <Polygon>& poly);
  double countAreasOdd(const std::vector <Polygon>& poly);
  double countAreasMean(const std::vector <Polygon>& poly);
  double countAreasVexes(const std::vector <Polygon>& poly, int numOfVexes);
  double maxArea(const std::vector<Polygon>& poly);
  double maxVexes(const std::vector<Polygon>& poly);
  double minArea(const std::vector<Polygon>& poly);
  double minVexes(const std::vector<Polygon>& poly);
  int countEven(const std::vector <Polygon>& poly);
  int countOdd(const std::vector <Polygon>& poly);
  int countPolys(const std::vector <Polygon>& poly, int numOfVexes);
  bool vexesEven(const Polygon& poly);
  bool vexesOdd(const Polygon& poly);
  bool numOfVexesEqual(const Polygon poly, size_t numOfVexes);
  int getNumVexes(const Polygon poly);
}

#endif

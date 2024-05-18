#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "dataStruct.hpp"

namespace evstigneev
{
  std::ostream& area(std::istream& in, std::ostream& out, std::vector<Polygon>& poly);
  std::ostream& max(std::istream& in, std::ostream& out, std::vector<Polygon>& poly);
  std::ostream& min(std::istream& in, std::ostream& out, std::vector<Polygon>& poly);
  std::ostream& count(std::istream& in, std::ostream& out, std::vector<Polygon>& poly);
  std::ostream& lessArea(std::istream& in, std::ostream& out, std::vector<Polygon>& poly);
  std::ostream& maxSeq(std::istream& in, std::ostream& out, std::vector<Polygon>& poly);
  double countArea(Polygon& poly);
  double sumAreaEven(double res, Polygon& poly);
  double sumAreaOdd(double res, Polygon& poly);
  double sumAreas(double res, Polygon& poly);
  double sumAreaEqual(double res, Polygon& poly, size_t numOfVexes);
  double countAreasEven(std::vector <Polygon>& poly);
  double countAreasOdd(std::vector <Polygon>& poly);
  double countAreasMean(std::vector <Polygon>& poly);
  double countAreasVexes(std::vector <Polygon>& poly, int numOfVexes);
  double maxArea(std::vector<Polygon>& poly);
  double maxVexes(std::vector<Polygon>& poly);
  double minArea(std::vector<Polygon>& poly);
  double minVexes(std::vector<Polygon>& poly);
  int countEven(const std::vector <Polygon>& poly);
  int countOdd(const std::vector <Polygon>& poly);
  int countPolys(const std::vector <Polygon>& poly, int numOfVexes);
  bool vexesEven(Polygon& poly);
  bool vexesOdd(Polygon& poly);
  bool numOfVexesEqual(Polygon poly, size_t numOfVexes);
}

#endif

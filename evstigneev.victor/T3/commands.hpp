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
  double sAreaEven(double res, const Polygon& poly);
  double sAreaOdd(double res, const Polygon& poly);
  double sArea(double res, const Polygon& poly);
  double sAreaEqual(double res, const Polygon& poly, size_t numOfVexes);
  double cAreaEven(const std::vector <Polygon>& poly);
  double cAreaOdd(const std::vector <Polygon>& poly);
  double cAreaMean(const std::vector <Polygon>& poly);
  double cAreaVexes(const std::vector <Polygon>& poly, int numOfVexes);
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
  int pair(const Point& f, const Point& s);
}

#endif

#include "commands.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <numeric>
#include <functional>

double evstigneev::countArea(const Polygon& poly) {
  double area = 0.0;
  for (size_t i = 0; i < poly.points.size() - 1; ++i) {
    area += poly.points[i].x * poly.points[i + 1].y - poly.points[i + 1].x * poly.points[i].y;
  }
  area += poly.points.back().x * poly.points.front().y - poly.points.front().x * poly.points.back().y;
  return std::abs(area) / 2.0;
}

double evstigneev::sumAreaEven(double res, const Polygon& poly)
{
  return (poly.points.size() % 2 == 0) ? res + countArea(poly) : res;
}

double evstigneev::sumAreaOdd(double res, const Polygon& poly)
{
  return (poly.points.size() % 2 != 0) ? res + countArea(poly) : res;
}

double evstigneev::sumAreas(double res, const Polygon& poly)
{
  return res + countArea(poly);
}

double evstigneev::sumAreaEqual(double res, const Polygon& poly, size_t numOfVexes)
{
  return (poly.points.size() == numOfVexes) ? res + countArea(poly) : res;
}

std::ostream& evstigneev::area(std::istream& in, std::ostream& out, const std::vector<Polygon>& poly)
{
  std::string cmd = "";
  in >> cmd;

  if (cmd == "ODD")
  {
    out << countAreasOdd(poly);
  }
  else if (cmd == "EVEN")
  {
    out << countAreasEven(poly);
  }
  else if (cmd == "MEAN")
  {
    out << countAreasMean(poly);
  }
  else
  {
    int numOfVexes = std::stoi(cmd);
    out << countAreasVexes(poly, numOfVexes);
  }
  return out;
}

double evstigneev::countAreasEven(const std::vector <Polygon>& poly)
{
  return std::accumulate(poly.cbegin(), poly.cend(), 0, sumAreaEven);
}

double evstigneev::countAreasOdd(const std::vector <Polygon>& poly)
{
  return std::accumulate(poly.cbegin(), poly.cend(), 0, sumAreaOdd);
}

double evstigneev::countAreasMean(const std::vector <Polygon>& poly)
{
  double areas = std::accumulate(poly.cbegin(), poly.cend(), 0, sumAreas);
  return areas / poly.size();
}

double evstigneev::countAreasVexes(const std::vector <Polygon>& poly, int numOfVexes)
{
  return std::accumulate(poly.cbegin(), poly.cend(), 0,
    std::bind(sumAreaEqual, std::placeholders::_1, std::placeholders::_2, numOfVexes));
}

std::ostream& evstigneev::max(std::istream& in, std::ostream& out, const std::vector<Polygon>& poly)
{
  std::string cmd = "";
  in >> cmd;
  if (cmd == "AREA")
  {
    out << maxArea(poly);
  }
  else if (cmd == "VERTEXES")
  {
    out << maxVexes(poly);
  }
  return out;
}

double evstigneev::maxArea(const std::vector<Polygon>& poly)
{
  std::vector<double> area(poly.size());
  std::transform(poly.begin(), poly.end(), area.begin(), countArea);
  return *std::max_element(area.begin(), area.end());
}

double evstigneev::maxVexes(const std::vector<Polygon>& poly)
{
  std::vector<int> numOfVexes(poly.size());
  std::transform(poly.begin(), poly.end(), numOfVexes.begin(), numOfVexes);
  return *std::max_element(numOfVexes.begin(), numOfVexes.end());
}

std::ostream& evstigneev::min(std::istream& in, std::ostream& out, const std::vector<Polygon>& poly)
{
  std::string cmd = "";
  in >> cmd;
  if (cmd == "AREA")
  {
    out << minArea(poly);
  }
  else if (cmd == "VERTEXES")
  {
    out << minVexes(poly);
  }
  return out;
}

double evstigneev::minArea(const std::vector<Polygon>& poly)
{
  std::vector<double> area(poly.size());
  std::transform(poly.begin(), poly.end(), area.begin(), countArea);
  return *std::min_element(area.begin(), area.end());
}

double evstigneev::minVexes(const std::vector<Polygon>& poly)
{
  std::vector<int> numOfVexes(poly.size());
  std::transform(poly.begin(), poly.end(), numOfVexes.begin(), numOfVexes);
  return *std::min_element(numOfVexes.begin(), numOfVexes.end());
}

std::ostream& evstigneev::count(std::istream& in, std::ostream& out,
  const std::vector<Polygon>& poly)
{
  std::string cmd = "";
  in >> cmd;
  if (cmd == "EVEN")
  {
    out << countEven(poly);
  }
  else if (cmd == "ODD")
  {
    out << countOdd(poly);
  }
  else
  {
    int numOfVexes = std::stoi(cmd);
    out << countPolys(poly, numOfVexes);
  }
  return out;
}

int evstigneev::countEven(const std::vector <Polygon>& poly)
{
  return std::count_if(poly.begin(), poly.end(), vexesEven);
}

int evstigneev::countOdd(const std::vector <Polygon>& poly)
{
  return std::count_if(poly.begin(), poly.end(), vexesOdd);
}

int evstigneev::countPolys(const std::vector <Polygon>& poly, int numOfVexes)
{
  return std::count_if(poly.begin(), poly.end(), std::bind(numOfVexesEqual, std::placeholders::_1, numOfVexes));
}

bool evstigneev::vexesEven(const Polygon& poly)
{
  return poly.points.size() % 2 == 0;
}

bool evstigneev::vexesOdd(const Polygon& poly)
{
  return poly.points.size() % 2 == 1;
}

bool evstigneev::numOfVexesEqual(const Polygon poly, size_t numOfVexes)
{
  return poly.points.size() == numOfVexes;
}

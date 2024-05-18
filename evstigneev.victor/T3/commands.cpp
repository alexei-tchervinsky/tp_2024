#include "Commands.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <numeric>
#include <functional>

double countArea(evstigneev::Polygon& poly) {
  double area = 0.0;
  for (size_t i = 0; i < poly.points.size() - 1; ++i) {
    area += poly.points[i].x * poly.points[i + 1].y - poly.points[i + 1].x * poly.points[i].y;
  }
  area += poly.points.back().x * poly.points.front().y - poly.points.front().x * poly.points.back().y;
  return std::abs(area) / 2.0;
}

double sumAreasIfEven(double res, evstigneev::Polygon& poly)
{
  return (poly.points.size() % 2 == 0) ? res + countArea(poly) : res;
}

double sumAreasIfOdd(double res, evstigneev::Polygon& poly)
{
  return (poly.points.size() % 2 != 0) ? res + countArea(poly) : res;
}

double sumAreas(double res, evstigneev::Polygon& poly)
{
  return res + countArea(poly);
}

double sumAreasIfEqual(double res, evstigneev::Polygon& poly, 
  size_t numOfVexes)
{
  return (poly.points.size() == numOfVexes) ? res + countArea(poly) : res;
}

std::ostream& evstigneev::area(std::istream& in, std::ostream& out, std::vector<Polygon>& poly)
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

double countAreasEven(std::vector <evstigneev::Polygon>& poly)
{
  return std::accumulate(poly.cbegin(), poly.cend(), 0, sumAreasIfEven);
}

double countAreasOdd(std::vector <evstigneev::Polygon>& poly)
{
  return std::accumulate(poly.cbegin(), poly.cend(), 0, sumAreasIfOdd);
}

double countAreasMean(std::vector <evstigneev::Polygon>& poly)
{
  double areas = std::accumulate(poly.cbegin(), poly.cend(), 0, sumAreas);
  return areas / poly.size();
}

double countAreasVexes(std::vector <evstigneev::Polygon>& poly, int numOfVexes)
{
  return std::accumulate(poly.cbegin(), poly.cend(), 0, 
    std::bind(sumAreasIfEqual, std::placeholders::_1, std::placeholders::_2, numOfVexes));
}

std::ostream& evstigneev::max(std::istream& in, std::ostream& out, std::vector<Polygon>& poly)
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

double maxArea(std::vector<evstigneev::Polygon>& poly)
{
  std::vector<double> area(poly.size());
  std::transform(poly.begin(), poly.end(), area.begin(), countArea);
  return *std::max_element(area.begin(), area.end());
}

double maxVexes(std::vector<evstigneev::Polygon>& poly)
{
  std::vector<int> numOfVexes(poly.size());
  std::transform(poly.begin(), poly.end(), numOfVexes.begin(), numOfVexes);
  return *std::max_element(numOfVexes.begin(), numOfVexes.end());
}

std::ostream& evstigneev::min(std::istream& in, std::ostream& out, std::vector<Polygon>& poly)
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

double minArea(std::vector<evstigneev::Polygon>& poly)
{
  std::vector<double> area(poly.size());
  std::transform(poly.begin(), poly.end(), area.begin(), countArea);
  return *std::min_element(area.begin(), area.end());
}

double minVexes(std::vector<evstigneev::Polygon>& poly)
{
  std::vector<int> numOfVexes(poly.size());
  std::transform(poly.begin(), poly.end(), numOfVexes.begin(), numOfVexes);
  return *std::min_element(numOfVexes.begin(), numOfVexes.end());
}

std::ostream& evstigneev::count(std::istream& in, std::ostream& out,
  std::vector<Polygon>& poly)
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

int countEven(const std::vector <evstigneev::Polygon>& poly)
{
  return std::count_if(poly.begin(), poly.end(), vexesEven);
}

int countOdd(const std::vector <evstigneev::Polygon>& poly)
{
  return std::count_if(poly.begin(), poly.end(), vexesOdd);
}

int countPolys(const std::vector <evstigneev::Polygon>& poly, int numOfVexes)
{
  return std::count_if(poly.begin(), poly.end(), std::bind(numOfVexesEqual, std::placeholders::_1, numOfVexes));
}

bool vexesEven(evstigneev::Polygon& poly)
{
  return poly.points.size() % 2 == 0;
}

bool vexesOdd(evstigneev::Polygon& poly)
{
  return poly.points.size() % 2 == 1;
}

bool numOfVexesEqual(evstigneev::Polygon poly, size_t numOfVexes)
{
  return poly.points.size() == numOfVexes;
}

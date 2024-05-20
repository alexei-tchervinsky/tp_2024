#include "commands.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <numeric>
#include <functional>

double evstigneev::countArea(const Polygon& poly) {
  std::vector<int> p(poly.points.size());
  std::transform(poly.points.cbegin()++, poly.points.cend(), poly.points.cbegin(),
    p.begin(), pair);
  p.push_back(pair(poly.points.front(), poly.points.back()));
  return std::abs(std::accumulate(p.cbegin(), p.cend(), 0)) / 2.0;
}

double evstigneev::sAreaEven(double res, const Polygon& poly)
{
  return (poly.points.size() % 2 == 0) ? res + countArea(poly) : res;
}

double evstigneev::sAreaOdd(double res, const Polygon& poly)
{
  return (poly.points.size() % 2 != 0) ? res + countArea(poly) : res;
}

double evstigneev::sArea(double res, const Polygon& poly)
{
  return res + countArea(poly);
}

double evstigneev::sAreaEqual(double res, const Polygon& poly, size_t numOfVexes)
{
  return (poly.points.size() == numOfVexes) ? res + countArea(poly) : res;
}

std::ostream& evstigneev::area(std::istream& in, std::ostream& out, const std::vector<Polygon>& poly)
{
  std::string cmd = "";
  in >> cmd;

  if (cmd == "ODD")
  {
    out << cAreaOdd(poly);
  }
  else if (cmd == "EVEN")
  {
    out << cAreaEven(poly);
  }
  else if (cmd == "MEAN")
  {
    out << cAreaMean(poly);
  }
  else
  {
    int numOfVexes = std::stoi(cmd);
    if (numOfVexes <= 2)
    {
      throw std::logic_error("incorrect command");
    }
    out << cAreaVexes(poly, numOfVexes) << "\n";
  }
  return out;
}

double evstigneev::cAreaEven(const std::vector <Polygon>& poly)
{
  return std::accumulate(poly.cbegin(), poly.cend(), 0, sAreaEven);
}

double evstigneev::cAreaOdd(const std::vector <Polygon>& poly)
{
  return std::accumulate(poly.cbegin(), poly.cend(), 0, sAreaOdd);
}

double evstigneev::cAreaMean(const std::vector <Polygon>& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("data is empty");
  }
  return std::accumulate(poly.cbegin(), poly.cend(), 0, sArea) / poly.size();
}

double evstigneev::cAreaVexes(const std::vector <Polygon>& poly, int numOfVexes)
{
  return std::accumulate(poly.cbegin(), poly.cend(), 0, std::bind(sAreaEqual,
    std::placeholders::_1, std::placeholders::_2, numOfVexes));
}

std::ostream& evstigneev::max(std::istream& in, std::ostream& out, const std::vector<Polygon>& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("data is empty");
  }
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
  else
  {
    throw std::logic_error("incorrect command");
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
  std::transform(poly.begin(), poly.end(), numOfVexes.begin(), getNumVexes);
  return *std::max_element(numOfVexes.begin(), numOfVexes.end());
}

std::ostream& evstigneev::min(std::istream& in, std::ostream& out, const std::vector<Polygon>& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("data is empty");
  }
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
  else
  {
    throw std::logic_error("incorrect command");
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
  std::transform(poly.cbegin(), poly.cend(), numOfVexes.begin(), getNumVexes);
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
    if (numOfVexes <= 2)
    {
      throw std::logic_error("incorrect command");
    }
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

int evstigneev::getNumVexes(const Polygon poly)
{
  return poly.points.size();
}

int evstigneev::pair(const Point& f, const Point& s)
{
  return f.x * s.y - f.y * s.x;
}

std::ostream& evstigneev::lessArea(std::istream& in, std::ostream& out,
  const std::vector<Polygon>& poly)
{
  Polygon polygon;
  if (in >> polygon)
  {
    return out << std::count_if(poly.cbegin(), poly.cend(), std::bind(isLessArea,
      std::placeholders::_1, polygon));
  }
}

std::ostream& evstigneev::maxSeq(std::istream& in, std::ostream& out,
  const std::vector<Polygon>& poly)
{
  Polygon polygon;
  in >> polygon;

  int maxSeq = 0;
  int curr = 0;

  for (const auto& p : poly)
  {
    if (p == polygon)
    {
      curr++;
      maxSeq = std::max(maxSeq, curr);
    }
    else
    {
      curr = 0;
    }
  }
  return out << maxSeq << "\n";
}

bool evstigneev::isLessArea(const Polygon& poly1, const Polygon& poly2)
{
  return countArea(poly1) < countArea(poly2);
}

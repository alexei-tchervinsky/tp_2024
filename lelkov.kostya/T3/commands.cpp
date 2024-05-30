#include "commands.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <iomanip>
#include <map>
#include <functional>
#include <string>
#include <cmath>

double lelkov::calculateTriangleArea(Point pointA, Point pointB, Point pointC)
{
  return 0.5 * abs((pointA.x * (pointB.y - pointC.y) + pointB.x * (pointC.y - pointA.y) + pointC.x * (pointA.y - pointB.y)));
}

double lelkov::calculatePolygonArea(std::vector<Point> polygon, size_t counter)
{
  if (counter < 3)
  {
    return 0;
  }
  else
  {
    return calculateTriangleArea(polygon[0], polygon[counter - 1], polygon[counter - 2]) + calculatePolygonArea(polygon, counter - 1);
  }
}

double lelkov::summation(const std::vector<Polygon>& polygons)
{
  std::vector< double > areas(polygons.size());
  std::transform
  (
    polygons.begin(),
    polygons.end(),
    areas.begin(),
    [](const Polygon& applicant) { return calculatePolygonArea(applicant.points, applicant.points.size()); }
  );
  std::function< double(std::vector< double >::const_iterator, std::vector< double >::const_iterator) > sumRecursive;
  sumRecursive = [&sumRecursive](std::vector< double >::const_iterator it, std::vector< double >::const_iterator end) -> double
    {
      if (it == end)
      {
        return 0;
      }
      std::vector< int > result(1);
      std::transform
      (
        it,
        it + 1,
        result.begin(),
        [&sumRecursive, end, it](int val) { return val + sumRecursive(it + 1, end); }
      );
      return result[0];
    };
  return sumRecursive(areas.begin(), areas.end());
}

void lelkov::oddArea(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  std::vector< Polygon > oddPolygons;
  std::copy_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(oddPolygons),
    [](const Polygon& applicant) { return (applicant.points.size() % 2); }
  );
  out << std::fixed << std::setprecision(1) << summation(oddPolygons) << '\n';
}

void lelkov::evenArea(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  std::vector< Polygon > evenPolygons;
  std::copy_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(evenPolygons),
    [](const Polygon& applicant) { return !(applicant.points.size() % 2); }
  );
  out << std::fixed << std::setprecision(1) << summation(evenPolygons) << '\n';
}

void lelkov::meanArea(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  if (allPolygons.empty())
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  else
  {
    out << std::fixed << std::setprecision(1) << summation(allPolygons) / allPolygons.size() << '\n';
  }
}

void lelkov::verticesArea(const std::vector<Polygon>& allPolygons, std::ostream& out, size_t vertices)
{
  std::vector< Polygon > verticesPolygons;
  std::copy_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(verticesPolygons),
    [vertices](const Polygon& applicant) { return (applicant.points.size() == vertices); }
  );
  out << std::fixed << std::setprecision(1) << summation(verticesPolygons) << '\n';
}

void lelkov::maxArea(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  std::vector< double > allAreas;
  std::transform
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(allAreas),
    [](const Polygon& applicant) { return calculatePolygonArea(applicant.points, applicant.points.size()); }
  );
  double maxElement = *std::max_element(allAreas.begin(), allAreas.end());
  out << std::fixed << std::setprecision(1) << maxElement << '\n';
}

void lelkov::maxVertices(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  std::vector< size_t > allVertices;
  std::transform
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(allVertices),
    [](const Polygon& applicant) { return (applicant.points.size()); }
  );
  size_t maxElement = *std::max_element(allVertices.begin(), allVertices.end());
  out << std::fixed << maxElement << '\n';
}

void lelkov::minArea(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  std::vector< double > allAreas;
  std::transform
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(allAreas),
    [](const Polygon& applicant) { return calculatePolygonArea(applicant.points, applicant.points.size()); }
  );
  double minElement = *std::min_element(allAreas.begin(), allAreas.end());
  out << std::fixed << std::setprecision(1) << minElement << '\n';
}

void lelkov::minVertices(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  std::vector< size_t > allVertices;
  std::transform
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(allVertices),
    [](const Polygon& applicant) -> size_t { return applicant.points.size(); }
  );
  size_t minElement = *std::min_element(allVertices.begin(), allVertices.end());
  out << std::fixed << minElement << '\n';
}

void lelkov::countEvenVertices(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  size_t count = std::count_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    [](const Polygon& applicant) { return !(applicant.points.size() % 2); }
  );
  out << std::fixed << count << '\n';
}

void lelkov::countOddVertices(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  size_t count = std::count_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    [](const Polygon& applicant) { return (applicant.points.size() % 2); }
  );
  out << std::fixed << count << '\n';
}

void lelkov::countVertices(const std::vector<Polygon>& allPolygons, std::ostream& out, size_t vertices)
{
  size_t count = std::count_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    [vertices](const Polygon& applicant) { return (applicant.points.size() == vertices); }
  );
  out << std::fixed << count << '\n';
}

void lelkov::commandArea(const std::vector<Polygon>& allPolygons, std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > commandKey;
  commandKey["EVEN"] = std::bind(evenArea, _1, _2);
  commandKey["ODD"] = std::bind(oddArea, _1, _2);
  commandKey["MEAN"] = std::bind(meanArea, _1, _2);
  std::string command;
  in >> command;
  try
  {
    commandKey.at(command)(allPolygons, out);
  }
  catch (const std::out_of_range& e)
  {
    if (!std::isalpha(command[0]))
    {
      size_t vertices = std::stoull(command);
      if (vertices < 3)
      {
        throw std::logic_error("<INVALID COMMAND>\n");
      }
      verticesArea(allPolygons, out, vertices);
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
  }
}

void lelkov::commandMax(const std::vector<Polygon>& allPolygons, std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > commandKey;
  commandKey["AREA"] = std::bind(maxArea, _1, _2);
  commandKey["VERTEXES"] = std::bind(maxVertices, _1, _2);
  std::string command;
  in >> command;
  try
  {
    if (allPolygons.size() == 0)
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
    commandKey.at(command)(allPolygons, out);
  }
  catch (const std::out_of_range& e)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
}

void lelkov::commandMin(const std::vector<Polygon>& allPolygons, std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > commandKey;
  commandKey["AREA"] = std::bind(minArea, _1, _2);
  commandKey["VERTEXES"] = std::bind(minVertices, _1, _2);
  std::string command;
  in >> command;
  try
  {
    if (allPolygons.size() == 0)
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
    commandKey.at(command)(allPolygons, out);
  }
  catch (const std::out_of_range& e)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
}

void lelkov::commandCount(const std::vector<Polygon>& allPolygons, std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > commandKey;
  commandKey["EVEN"] = std::bind(countEvenVertices, _1, _2);
  commandKey["ODD"] = std::bind(countOddVertices, _1, _2);
  std::string command;
  in >> command;
  try
  {
    commandKey.at(command)(allPolygons, out);
  }
  catch (const std::out_of_range& e)
  {
    if (!std::isalpha(command[0]))
    {
      size_t vertices = std::stoull(command);
      if (vertices < 3)
      {
        throw std::logic_error("<INVALID COMMAND>\n");
      }
      countVertices(allPolygons, out, vertices);
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
  }
}

bool lelkov::isRectangle(const Polygon& poly, size_t index)
{
  if (index == poly.points.size())
  {
    return (poly.points.size() == 4) && (std::count(poly.points.begin(), poly.points.end(), poly.points[0]) == 1);
  }
  const Point& currentPoint = poly.points[index];
  bool allUniqueBefore = std::none_of
  (
    poly.points.begin(),
    poly.points.begin() + index,
    [&](const Point& applicant) { return applicant == currentPoint; }
  );
  return allUniqueBefore && isRectangle(poly, index + 1);
}

void lelkov::isRects(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  size_t count = std::count_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    [](const Polygon& applicant) { return isRectangle(applicant, 0); }
  );
  out << std::fixed << count << '\n';
}

void lelkov::commandRects(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  try
  {
    isRects(allPolygons, out);
  }
  catch (const std::out_of_range& e)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
}

double lelkov::calculateSideLength(const Point& head, const Point& tail)
{
  return std::sqrt(std::pow(tail.x - head.x, 2) + std::pow(tail.y - head.y, 2));
}

void lelkov::getAllSideLengths(const Polygon& poly, std::vector<double>& sideLengths, size_t index)
{
  if (index == poly.points.size())
  {
    return;
  }
  const Point& currentPoint = poly.points[index];
  const Point& nextPoint = poly.points[(index + 1) % poly.points.size()];
  double sideLength = calculateSideLength(currentPoint, nextPoint);
  sideLengths.push_back(sideLength);
  getAllSideLengths(poly, sideLengths, index + 1);
}

bool lelkov::arePolygonsSame(const Polygon& applicant, const Polygon& overlay)
{
  std::vector<double> sideLengthsAplicant;
  getAllSideLengths(applicant, sideLengthsAplicant, 0);
  std::vector<double> sideLengthsOverlay;
  getAllSideLengths(overlay, sideLengthsOverlay, 0);
  std::sort(sideLengthsAplicant.begin(), sideLengthsAplicant.end());
  std::sort(sideLengthsOverlay.begin(), sideLengthsOverlay.end());
  return sideLengthsOverlay == sideLengthsAplicant;
}

void lelkov::countSamePolygons(const std::vector<Polygon>& allPolygons, const Polygon& overlay, std::ostream& out)
{
  size_t count = std::count_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    [overlay](const Polygon& applicant) { return arePolygonsSame(applicant, overlay); }
  );
  out << std::fixed << count << '\n';
}

void lelkov::commandSame(const std::vector<Polygon>& allPolygons, std::istream& in, std::ostream& out)
{
  Polygon overlay;
  in >> overlay;
  if (in.fail())
  {
    throw std::logic_error("< WRONG INPUT >\n");
  }
  try
  {
    countSamePolygons(allPolygons, overlay, out);
  }
  catch (const std::out_of_range& e)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
}
std::ostream& lelkov::outError(std::ostream& out, const std::string& errorMessage) {
    out << errorMessage << '\n';
    return out;
}


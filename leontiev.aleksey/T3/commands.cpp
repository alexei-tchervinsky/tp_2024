#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <exception>
#include <numeric>


using namespace std::placeholders;

std::ostream& leontiev::calculateArea(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::string argument = "";
  in >> argument;
  out << std::fixed << std::setprecision(1);
  if (argument == "ODD")
  {
    out << calculateOddArea(polygons) << "\n";
  }
  else if (argument == "EVEN")
  {
    out << calculateEvenArea(polygons) << "\n";
  }
  else if (argument == "MEAN")
  {
    out << calculateMeanArea(polygons) << "\n";
  }
  else
  {
    int vertexCounter = std::stoi(argument);
    if (vertexCounter < 3)
    {
      throw std::logic_error("Invalid argument");
    }
    out << calculateVertexes(polygons, vertexCounter) << "\n";
  }
  return out;
}

double leontiev::calculateOddArea(const std::vector<Polygon>& polygons)
{
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0, oddAreasSum);
}

double leontiev::calculateEvenArea(const std::vector<Polygon>& polygons)
{
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0, evenAreasSum);
}

double leontiev::calculateMeanArea(const std::vector<Polygon>& polygons)
{
  if (polygons.empty())
  {
    throw std::logic_error("Invalid argument");
  }
  double allAreas = std::accumulate(polygons.cbegin(), polygons.cend(), 0, areasSum);
  return allAreas / polygons.size();
}

double leontiev::calculateVertexes(const std::vector<Polygon>& polygons, int vertexNum)
{
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0, std::bind(equalAreasSum, _1, _2, vertexNum));
}

int leontiev::pairDifference(const Point& first, const Point& second)
{
  return first.x * second.y - first.y * second.x;
}

double leontiev::areaCount(const Polygon& polygon)
{
  std::vector<int> pairs(polygon.points.size());
  std::transform(++polygon.points.cbegin(), polygon.points.cend(), polygon.points.cbegin(), pairs.begin(), pairDifference);
  pairs.push_back(pairDifference(polygon.points.front(), polygon.points.back()));
  int area = std::accumulate(pairs.cbegin(), pairs.cend(), 0);
  return abs(area) / 2.0;
}

double leontiev::areasSum(double result, const Polygon& polygon)
{
  return result + areaCount(polygon);
}

double leontiev::evenAreasSum(double result, const Polygon& polygon)
{
  if (polygon.points.size() % 2 == 0)
  {
    return result + areaCount(polygon);
  }
  else
  {
    return result;
  }
}

double leontiev::oddAreasSum(double result, const Polygon& polygon)
{
  if (polygon.points.size() % 2 != 0)
  {
    return result + areaCount(polygon);
  }
  else
  {
    return result;
  }
}

double leontiev::equalAreasSum(double result, const Polygon& polygon, std::size_t vertexNum)
{
  if (polygon.points.size() == vertexNum)
  {
    return result + areaCount(polygon);
  }
  else
  {
    return result;
  }
}

std::ostream& leontiev::getMax(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  if (polygons.empty())
  {
    throw std::logic_error("There is no data");
  }
  std::string argument = "";
  in >> argument;
  if (argument == "AREA")
  {
    out << std::fixed << std::setprecision(1) << getMaxArea(polygons) << "\n";
  }
  else if (argument == "VERTEXES")
  {
    out << std::fixed << std::setprecision(0) << getMaxVertexes(polygons) << "\n";
  }
  else
  {
    throw std::logic_error("Invalid argument");
  }
  return out;
}

double leontiev::getMaxArea(const std::vector<Polygon>& polygons)
{
  std::vector<double> allAreas(polygons.size());
  std::transform(polygons.begin(), polygons.end(), allAreas.begin(), areaCount);
  double maxArea = *std::max_element(allAreas.begin(), allAreas.end());
  return maxArea;
}

int leontiev::vertexCount(const Polygon& polygon)
{
  return polygon.points.size();
}

double leontiev::getMaxVertexes(const std::vector<Polygon>& polygons)
{
  std::vector<int> allVertexes(polygons.size());
  std::transform(polygons.begin(), polygons.end(), allVertexes.begin(), vertexCount);
  return *std::max_element(allVertexes.begin(), allVertexes.end());
}

std::ostream& leontiev::getMin(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  if (polygons.empty())
  {
    throw std::logic_error("There is no data");
  }
  std::string argument = "";
  in >> argument;
  if (argument == "AREA")
  {
    out << std::fixed << std::setprecision(1) << getMinArea(polygons) << "\n";
  }
  else if (argument == "VERTEXES")
  {
    out << std::fixed << std::setprecision(0) << getMinVertexes(polygons) << "\n";
  }
  else
  {
    throw std::logic_error("Invalid argument");
  }
  return out;
}

double leontiev::getMinArea(const std::vector<Polygon>& polygons)
{
  std::vector<double> allAreas(polygons.size());
  std::transform(polygons.begin(), polygons.end(), allAreas.begin(), areaCount);
  return *std::min_element(allAreas.begin(), allAreas.end());

}

double leontiev::getMinVertexes(const std::vector<Polygon>& polygons)
{
  std::vector<int> allVertexes(polygons.size());
  std::transform(polygons.begin(), polygons.end(), allVertexes.begin(), vertexCount);
  return *std::min_element(allVertexes.begin(), allVertexes.end());
}

std::ostream& leontiev::count(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::string argument = "";
  in >> argument;
  out << std::fixed << std::setprecision(1);
  if (argument == "ODD")
  {
    out << oddCount(polygons) << "\n";
  }
  else if (argument == "EVEN")
  {
    out << evenCount(polygons) << "\n";
  }
  else
  {
    int vertexCounter = std::stoi(argument);
    if (vertexCounter < 3)
    {
      throw std::logic_error("Invalid argument");
    }
    out << shapeCount(polygons, vertexCounter) << "\n";
  }
  return out;
}
int leontiev::evenCount(const std::vector<Polygon>& polygons)
{
  return std::count_if(polygons.begin(), polygons.end(), isVertexEven);
}

int leontiev::oddCount(const std::vector<Polygon>& polygons)
{
  return std::count_if(polygons.begin(), polygons.end(), isVertexOdd);
}

bool leontiev::isVertexEven(const Polygon polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool leontiev::isVertexOdd(const Polygon polygon)
{
  return polygon.points.size() % 2 != 0;
}

bool leontiev::isVertexEqual(const Polygon polygon, std::size_t verteNum)
{
  return polygon.points.size() == verteNum;
}

int leontiev::shapeCount(const std::vector<Polygon>& polygons, int vertexNum)
{
  return std::count_if(polygons.begin(), polygons.end(), std::bind(isVertexEqual, _1, vertexNum));
}

int leontiev::getX(const Point& point)
{
  return point.x;
}

int leontiev::getY(const Point& point)
{
  return point.y;
}

int leontiev::getMaxCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point))
{
  std::vector<int> allCoordinates;
  std::transform(polygon.points.begin(), polygon.points.end(), std::back_inserter(allCoordinates), getCoordinate);
  int max = *std::max_element(allCoordinates.begin(), allCoordinates.end());
  return max;
}

int leontiev::getMinCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point))
{
  std::vector<int> allCoordinates;
  std::transform(polygon.points.begin(), polygon.points.end(), std::back_inserter(allCoordinates), getCoordinate);
  int min = *std::min_element(allCoordinates.begin(), allCoordinates.end());
  return min;
}

std::vector<leontiev::Point> leontiev::getFrame(const std::vector<Polygon>& polygons)
{
  std::vector<int> allMaxX;
  std::vector<int> allMaxY;
  std::vector<int> allMinX;
  std::vector<int> allMinY;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(allMaxX), std::bind(getMaxCoordinate, _1, getX));
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(allMaxY), std::bind(getMaxCoordinate, _1, getY));
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(allMinX), std::bind(getMinCoordinate, _1, getX));
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(allMinY), std::bind(getMinCoordinate, _1, getY));
  int maxX = *std::max_element(allMaxX.begin(), allMaxX.end());
  int maxY = *std::max_element(allMaxY.begin(), allMaxY.end());
  int minX = *std::min_element(allMinX.begin(), allMinX.end());
  int minY = *std::min_element(allMinY.begin(), allMinY.end());
  std::vector <Point> frame;
  frame.push_back(Point{minX, maxY});
  frame.push_back(Point{maxX, maxY});
  frame.push_back(Point{maxX, minY});
  frame.push_back(Point{minX, minY});
  return frame;
}
bool leontiev::isInFrame(const std::vector<Polygon>& polygons, const Polygon& polygon)
{
  std::vector< Point > frame = getFrame(polygons);
  int maxFrameX = frame[1].x;
  int minFrameX = frame[0].x;
  int maxFrameY = frame[0].y;
  int minFrameY = frame[2].y;
  int maxPolygonX = getMaxCoordinate(polygon, getX);
  int minPolygonX = getMinCoordinate(polygon, getX);
  int maxPolygonY = getMaxCoordinate(polygon, getY);
  int minPolygonY = getMinCoordinate(polygon, getY);
  bool noMoreMax = maxPolygonX <= maxFrameX || maxPolygonY <= maxFrameY;
  bool noLessMin = minPolygonX >= minFrameX || minPolygonY >= minFrameY;
  if(noMoreMax && noLessMin)
  {
    return true;
  }
  else
  {
    return false;
  }
}

std::ostream& leontiev::inFrame(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  Polygon polygon;
  in >> polygon;
  if (!in)
  {
    throw std::logic_error("");
  }
  else
  {
    if (isInFrame(polygons, polygon))
    {
      out << "<TRUE>\n";
    }
    else
    {
      out << "<FALSE>\n";
    }
  }
  return out;
}

bool leontiev::isEquaPoints(const Point& first, const Point& second)
{
  return first.x == second.x && first.y == second.y;
}
bool leontiev::isEqualPolygons(const Polygon& first, const Polygon& second)
{
  if (second.points.size() == first.points.size())
  {
    return std::equal(std::begin(first.points), std::end(first.points), std::begin(second.points), std::end(second.points));
  }
}

std::ostream& leontiev::maxSeq(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  Polygon polygon;
  in >> polygon;
  if (!in)
  {
    throw std::logic_error("");
  }
  else
  {
    out << std::count_if(polygons.begin(), polygons.end(), std::bind(isEqualPolygons, _1, polygon));
  }
}

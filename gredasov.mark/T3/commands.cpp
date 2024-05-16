#include <numeric>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <functional>

#include "commands.hpp"
#include "scopeguard.hpp"

void gredasov::getAreaCommand(const std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  iofmtguard fguard(out);
  std::string str = "";
  in >> str;
  out << std::fixed << std::setprecision(1);
  if (str == "EVEN")
  {
    outputMessage(out, sumOfEvenAreas(polygons));
  }
  else if (str == "ODD")
  {
    outputMessage(out, sumOfOddAreas(polygons));
  }
  else if (str == "MEAN")
  {
    outputMessage(out, sumOfMeanAreas(polygons));
  }
  else
  {
    int num = std::stoi(str);
    if (num <= 2)
    {
      throw std::logic_error("Wrong number of vertexes");
    }
    else
    {
      outputMessage(out, sumOfNumAreas(polygons, num));
    }
  }
}

double gredasov::addArea(double accumulator, const Polygon& polygon)
{
  return accumulator + getArea(polygon);
}

double gredasov::addEvenArea(double accumulator, const Polygon& polygon)
{
  if (polygon.pts.size() % 2 == 0)
  {
    return accumulator + getArea(polygon);
  }
  return accumulator;
}

double gredasov::addOddArea(double accumulator, const Polygon& polygon)
{
  if (polygon.pts.size() % 2 == 1)
  {
    return accumulator + getArea(polygon);
  }
  return accumulator;
}

double gredasov::sumOfAreas(const std::vector< Polygon >& polygons)
{
  return std::accumulate(polygons.begin(), polygons.end(), 0.0, addArea);
}

double gredasov::sumOfEvenAreas(const std::vector<Polygon>& polygons)
{
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, addEvenArea);
}

double gredasov::sumOfOddAreas(const std::vector<Polygon>& polygons)
{
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, addOddArea);
}

double gredasov::sumOfMeanAreas(const std::vector<Polygon>& polygons)
{
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, addArea) / polygons.size();
}

double gredasov::sumOfNumAreas(const std::vector<Polygon>& polygons, std::size_t num)
{
  return std::accumulate(
    polygons.cbegin(),
    polygons.cend(),
    0.0,
    [num](double accumulator, const Polygon& polygon)
    {
      if (polygon.pts.size() == num)
      {
        return accumulator + getArea(polygon);
      }
      return accumulator;
    }
  );
}

double gredasov::getArea(const Polygon& polygon)
{
  std::vector< int > pairs(polygon.pts.size());

  std::transform(
    polygon.pts.begin() + 1,
    polygon.pts.end(),
    polygon.pts.begin(),
    pairs.begin(),
    [](const Point & p1, const Point & p2)
    {
      return p1.x * p2.y - p1.y * p2.x;
    }
  );

  pairs.push_back(polygon.pts.front().x * polygon.pts.back().y - polygon.pts.front().y * polygon.pts.back().x);

  return 0.5 * abs(std::accumulate(pairs.cbegin(), pairs.cend(), 0));
}

void gredasov::getMaxCommand(const std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  iofmtguard fguard(out);
  std::string str = "";
  in >> str;
  out << std::fixed << std::setprecision(1);
  std::size_t parameter = 1;
  if (str == "AREA")
  {
    outputMessage(out, getMinMaxArea(polygons, parameter));
  }
  else if (str == "VERTEXES")
  {
    outputMessage(out, getMinMaxVertexes(polygons, parameter));
  }
  else
  {
    throw std::logic_error("Wrong parameter after MAX");
  }
}

double gredasov::getMinMaxArea(const std::vector< Polygon >& polygons, std::size_t& parameter)
{
  std::vector< double > areas(polygons.size());
  std::transform(
  polygons.begin(),
  polygons.end(),
  areas.begin(),
  getArea);

  auto it = std::minmax_element(areas.begin(), areas.end());
  double max = *it.second;
  double min = *it.first;

  if (parameter == 1)
  {
    return max;
  }
  return min;
}

std::size_t gredasov::getMinMaxVertexes(const std::vector< Polygon >& polygons, std::size_t& parameter)
{
  std::vector< double > vertexes(polygons.size());
  std::transform(
    polygons.begin(),
    polygons.end(),
    vertexes.begin(),
    [](const Polygon& polygon)
    {
      return polygon.pts.size();
    }
  );

  auto it = std::minmax_element(vertexes.begin(), vertexes.end());
  std::size_t max = *it.second;
  std::size_t min = *it.first;

  if (parameter == 1)
  {
    return max;
  }
  return min;
}

void gredasov::getMinCommand(const std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  iofmtguard fguard(out);
  std::string str = "";
  in >> str;
  out << std::fixed << std::setprecision(1);
  std::size_t parameter = 2;
  if (str == "AREA")
  {
    outputMessage(out, getMinMaxArea(polygons, parameter));
  }
  else if (str == "VERTEXES")
  {
    outputMessage(out, getMinMaxVertexes(polygons, parameter));
  }
  else
  {
    throw std::logic_error("Wrong parameter after MIN");
  }
}

void gredasov::getCountCommand(const std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  iofmtguard fguard(out);
  std::string str = "";
  in >> str;
  if(str == "EVEN")
  {
    outputMessage(out, getCountOfEven(polygons));
  }
  else if (str == "ODD")
  {
    outputMessage(out, getCountOfOdd(polygons));
  }
  else
  {
    int num = std::stoi(str);
    if (num <= 2)
    {
      throw std::logic_error("Wrong number of vertexes");
    }
    else
    {
      outputMessage(out, getCountOfNum(polygons, num));
    }
  }
}

std::size_t gredasov::getCountOfEven(const std::vector< Polygon >& polygons)
{
  return std::count_if(
    polygons.begin(),
    polygons.end(),
    [](const Polygon& polygon)
    {
      return (polygon.pts.size() % 2 == 0);
    }
  );
}

std::size_t gredasov::getCountOfOdd(const std::vector< Polygon >& polygons)
{
  return std::count_if(
    polygons.begin(),
    polygons.end(),
    [](const Polygon& polygon)
    {
      return (polygon.pts.size() % 2 == 1);
    }
  );
}

std::size_t gredasov::getCountOfNum(const std::vector< Polygon >& polygons, std::size_t num)
{
  return std::count_if(
    polygons.begin(),
    polygons.end(),
    [num](const Polygon& polygon)
    {
      return (polygon.pts.size() == num);
    }
  );
}

void gredasov::isInFrameCommand(const std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  if (polygons.empty())
  {
    throw std::logic_error("No polygons in input");
  }
  iofmtguard fguard(out);
  Polygon frame = getFrame(polygons);
  Polygon polygon;
  if (!(in >> polygon))
  {
    throw std::logic_error("Wrong input after INFRAME");
  }
  if (isInFrame(polygons, polygon))
  {
    outputMessage(out, "<TRUE>");
  }
  else
  {
    outputMessage(out, "<FALSE>");
  }
}

int gredasov::getMinMaxX(const Polygon& polygon, std::size_t parameter)
{
  std::vector< int > ptsX(polygon.pts.size());
  std::transform(
    polygon.pts.cbegin(),
    polygon.pts.cend(),
    ptsX.begin(),
    [](const Point& p)
    {
      return p.x;
    }
  );
  int maxX = *max_element(ptsX.begin(), ptsX.end());
  int minX = *min_element(ptsX.begin(), ptsX.end());

  if (parameter == 1)
  {
    return maxX;
  }
  return minX;
}

int gredasov::getMinMaxY(const Polygon& polygon, std::size_t parameter)
{
  std::vector< int > ptsY(polygon.pts.size());
  std::transform(
    polygon.pts.cbegin(),
    polygon.pts.cend(),
    ptsY.begin(),
    [](const Point& p)
    {
      return p.y;
    }
  );
  int maxY = *max_element(ptsY.begin(), ptsY.end());
  int minY = *min_element(ptsY.begin(), ptsY.end());

  if (parameter == 1)
  {
    return maxY;
  }
  return minY;
}

gredasov::Polygon gredasov::getFrame(const std::vector< Polygon >& polygons)
{
  std::vector<int> ptsMaxX(polygons.size());
  std::size_t parameter = 1;
  std::transform(
    polygons.cbegin(),
    polygons.cend(),
    ptsMaxX.begin(),
    std::bind(getMinMaxX, std::placeholders::_1, parameter)
  );
  int rightTopX = *max_element(ptsMaxX.begin(), ptsMaxX.end());

  std::vector<int> ptsMinX(polygons.size());
  parameter = 2;
  std::transform(
    polygons.cbegin(),
    polygons.cend(),
    ptsMinX.begin(),
    std::bind(getMinMaxX, std::placeholders::_1, parameter)
  );
  int leftBottomX = *min_element(ptsMinX.begin(), ptsMinX.end());

  std::vector<int> ptsMaxY(polygons.size());
  parameter = 1;
  std::transform(
    polygons.cbegin(),
    polygons.cend(),
    ptsMaxY.begin(),
    std::bind(getMinMaxY, std::placeholders::_1, parameter)
  );
  int rightTopY = *max_element(ptsMaxY.begin(), ptsMaxY.end());

  std::vector<int> ptsMinY(polygons.size());
  parameter = 2;
  std::transform(
    polygons.cbegin(),
    polygons.cend(),
    ptsMinY.begin(),
    std::bind(getMinMaxY, std::placeholders::_1, parameter)
  );
  int leftBottomY = *min_element(ptsMinY.begin(), ptsMinY.end());

  Polygon frame;
  frame.pts.push_back({ leftBottomX, leftBottomY });
  frame.pts.push_back({ rightTopX, rightTopY });

  return frame;
}

bool gredasov::isInFrame(const std::vector< Polygon >& polygons, const Polygon& polygon)
{
  Polygon frame = getFrame(polygons);
  int minX = frame.pts.at(0).x;
  int maxX = frame.pts.at(1).x;
  int minY = frame.pts.at(0).y;
  int maxY = frame.pts.at(1).y;

  int pMaxX = getMinMaxX(polygon, 1);
  int pMinX = getMinMaxX(polygon, 2);
  int pMaxY = getMinMaxY(polygon, 1);
  int pMinY = getMinMaxY(polygon, 2);

  if ((pMaxX <= maxX) && (pMaxY <= maxY) && (pMinX >= minX) && (pMinY >= minY))
  {
    return true;
  }
  return false;
}

void gredasov::getIntersectionsCommand(const std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  if (polygons.empty())
  {
    throw std::logic_error("No polygons in input");
  }
  Polygon polygon;
  if (!(in >> polygon))
  {
    throw std::logic_error("Wrong input after INTERSECTIONS");
  }
  out << std::count_if(
    polygons.begin(),
    polygons.end(),
    [&polygon](const Polygon& p)
    {
      return areTwoPolygonsIntersected(p, polygon);
    }
  ) << '\n';
}

bool gredasov::isPointInPolygon(const Polygon& polygon, const Point& point)
{
  std::vector<std::pair<Point, Point>> edges;
  std::transform(
    polygon.pts.begin(),
    polygon.pts.end() - 1,
    polygon.pts.begin() + 1,
    std::back_inserter(edges),
    [](const Point& a, const Point& b)
    {
      return std::make_pair(a, b);
    }
  );
  edges.push_back(std::make_pair(polygon.pts.back(), polygon.pts.front()));

  return std::any_of(
    edges.begin(),
    edges.end(),
    [&point](const std::pair<Point, Point>& edge)
    {
      const Point& p1 = edge.first;
      const Point& p2 = edge.second;

      if ((p1.y < point.y && p2.y >= point.y || p2.y < point.y && p1.y >= point.y) &&
          (p1.x + (point.y - p1.y) / (p2.y - p1.y) * (p2.x - p1.x) < point.x))
      {
        return true;
      }
      return false;
    }
  );
}

bool gredasov::areTwoPolygonsIntersected(const Polygon& p1, const Polygon& p2)
{
  if (std::any_of(
    p1.pts.begin(),
    p1.pts.end(),
    [&p2](const Point& point)
    {
      return isPointInPolygon(p2, point);
    }
  ))
  {
    return true;
  }

  if (std::any_of(
    p2.pts.begin(),
    p2.pts.end(),
    [&p1](const Point& point)
    {
      return isPointInPolygon(p1, point);
    }
  ))
  {
    return true;
  }

  return false;
}

void gredasov::outputMessage(std::ostream& out, std::size_t message)
{
  out << message << '\n';
}

void gredasov::outputMessage(std::ostream& out, double message)
{
  out << std::fixed << std::setprecision(1) << message << '\n';
}

void gredasov::outputMessage(std::ostream& out, std::string message)
{
  out << message << '\n';
}


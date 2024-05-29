#include "commands.h"
#include <cmath>
#include <exception>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cctype>

bylinskiy::Point pointsDifference(const bylinskiy::Point & first, const bylinskiy::Point & second)
{
  return bylinskiy::Point{second.x - first.x, second.y - first.y};
}

bool isSame(bylinskiy::Polygon first, bylinskiy::Polygon second)
{
  if (first.points.size() != second.points.size())
  {
    return false;
  }
  std::vector< bylinskiy::Point > firstDiffs(first.points.size() - 1);
  std::vector< bylinskiy::Point > secondDiffs(first.points.size() - 1);
  using namespace std::placeholders;
  std::transform(first.points.cbegin() + 1, first.points.cend(), firstDiffs.begin(), std::bind(pointsDifference, _1, first.points[0]));
  std::transform(second.points.cbegin() + 1, second.points.cend(), secondDiffs.begin(), std::bind(pointsDifference, _1, second.points[0]));
  return (firstDiffs == secondDiffs);
}

void bylinskiy::same(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  bylinskiy::Polygon context;
  in >> context;
  if (!in || in.peek() != '\n')
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  using namespace std::placeholders;
  out << std::count_if(polygons.cbegin(), polygons.cend(), std::bind(isSame, _1, context)) << "\n";
}

bool isAreaLess(bylinskiy::Polygon polygon, double area)
{
  return (getArea(polygon) < area);
}

void bylinskiy::lessArea(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  bylinskiy::Polygon context;
  in >> context;
  if (!in || in.peek() != '\n')
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  using namespace std::placeholders;
  out << std::count_if(polygons.cbegin(), polygons.cend(), std::bind(isAreaLess, _1, getArea(context))) << "\n";
}

bool numOfVertexes(const bylinskiy::Polygon & polygon, size_t num)
{
  return (polygon.points.size() == num);
}

bool evenOrOdd(const bylinskiy::Polygon & polygon, bool isOdd)
{
  return (polygon.points.size() % 2 == isOdd);
}

void bylinskiy::count(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  std::string context;
  in >> context;
  std::function< size_t(const bylinskiy::Polygon &) > func;
  using namespace std::placeholders;
  if (context == "EVEN")
  {
    func = std::bind(evenOrOdd, _1, false);
  }
  else if (context == "ODD")
  {
    func = std::bind(evenOrOdd, _1, true);
  }
  else if (std::all_of(context.cbegin(), context.cend(), ::isdigit) && std::stoi(context) > 2)
  {
    func = std::bind(numOfVertexes, _1, std::stoi(context));
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  out << std::count_if(polygons.cbegin(), polygons.cend(), func) << "\n";
}

size_t getVertex(const bylinskiy::Polygon & polygon)
{
  return polygon.points.size();
}

size_t maxVertexes(const std::vector< bylinskiy::Polygon > polygons)
{
  std::vector < size_t > vertexes(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), vertexes.begin(), getVertex);
  return *max_element(vertexes.cbegin(), vertexes.cend());
}

size_t minVertexes(const std::vector< bylinskiy::Polygon > polygons)
{
  std::vector < size_t > vertexes(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), vertexes.begin(), getVertex);
  return *min_element(vertexes.cbegin(), vertexes.cend());
}

double minArea(const std::vector< bylinskiy::Polygon > polygons)
{
  std::vector < double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), bylinskiy::getArea);
  return *min_element(areas.cbegin(), areas.cend());
}

double maxArea(const std::vector< bylinskiy::Polygon > polygons)
{
  std::vector < double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), bylinskiy::getArea);
  return *max_element(areas.cbegin(), areas.cend());
}

void bylinskiy::minVertexOrArea(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  std::string context;
  in >> context;
  if (polygons.size() < 1)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  else if (context == "AREA")
  {
    out << std::setprecision(1) << std::fixed << minArea(polygons);
  }
  else if (context == "VERTEXES")
  {
    out << minVertexes(polygons);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  out << "\n";
}

void bylinskiy::maxVertexOrArea(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  std::string context;
  in >> context;
  if (polygons.size() < 1)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  else if (context == "AREA")
  {
    out << std::setprecision(1) << std::fixed << maxArea(polygons) ;
  }
  else if (context == "VERTEXES")
  {
    out << maxVertexes(polygons);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  out << "\n";
}

double evenOrOddArea(const bylinskiy::Polygon & polygon, bool isOdd)
{
  if (evenOrOdd(polygon, isOdd))
  {
    return getArea(polygon);
  }
  else
  {
    return 0;
  }
}

double numOfVertexesArea(const bylinskiy::Polygon & polygon, size_t num)
{
  if (numOfVertexes(polygon, num))
  {
    return getArea(polygon);
  }
  else
  {
    return 0;
  }
}

void bylinskiy::area(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  std::string context;
  in >> context;
  std::function< double(const bylinskiy::Polygon &) > func;
  using namespace std::placeholders;
  if (context == "EVEN")
  {
    func = std::bind(evenOrOddArea, _1, false);
  }
  else if (context == "ODD")
  {
    func = std::bind(evenOrOddArea, _1, true);
  }
  else if (context == "MEAN" && polygons.size() > 0)
  {
    func = getArea;
  }
  else if (std::all_of(context.cbegin(), context.cend(), ::isdigit) && std::stoi(context) > 2)
  {
    func = std::bind(numOfVertexesArea, _1, std::stoi(context));
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  std::vector < double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), func);
  double sum = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  if (context == "MEAN")
  {
    sum /= polygons.size();
  }
  out << std::setprecision(1) << std::fixed << sum << "\n";
}

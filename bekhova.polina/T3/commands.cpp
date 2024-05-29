#include "commands.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <functional>
#include <numeric>
#include <iomanip>
#include <string>
#include <cmath>

void bekhova::Area(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::map<std::string, std::function<void(const std::vector<Polygon>& polygon, std::ostream& out)>> areas;
  areas["EVEN"] = AreaEven;
  areas["ODD"] = AreaOdd;
  areas["MEAN"] = AreaMean;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<COMMAND IS INVALID>\n");
  std::string parameter;
  in >> parameter;
  try
  {
    areas.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range& ex)
  {
    if (std::isdigit(parameter[0]) && std::stoi(parameter) > 2)
    {
      AreaVersNum(std::stoi(parameter), polygons, out);
    }
    else
    {
      outInvalid(out);
    }
  }
}

void bekhova::AreaEven(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<Polygon> EvenPolygons_vec;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(EvenPolygons_vec),
    [](const Polygon& polygon)
    {
      return !(polygon.points.size() % 2);
    });
  double sum = sumAreas(EvenPolygons_vec);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

void bekhova::AreaOdd(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<Polygon> OddPolygons_vec;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(OddPolygons_vec),
    [](const Polygon& polygon)
    {
      return (polygon.points.size() % 2);
    });
  double sum = sumAreas(OddPolygons_vec);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

void bekhova::AreaMean(const std::vector<Polygon>& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::out_of_range("");
  }
  double sum = sumAreas(polygons);
  out << std::setprecision(1) << std::fixed << sum / polygons.size() << '\n';
}

void bekhova::AreaVersNum(std::size_t vertexes, const std::vector<Polygon>& polygons, std::ostream& out)
{
  auto NVertexes = std::bind(std::equal_to<size_t>{}, vertexes, std::placeholders::_1);
  std::vector<Polygon> polygonsWithNVertexes;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(polygonsWithNVertexes),
    [NVertexes](const Polygon& polygon)
    {
      return NVertexes(polygon.points.size());
    });

  double sum = sumAreas(polygonsWithNVertexes);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

double bekhova::sumAreas(const std::vector<Polygon>& polygons)
{
  std::vector<double> AreasOfPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(AreasOfPolygons_vec),
    [](const Polygon& polygon)
    {
      return getArea(polygon);
    });

  double sumOfAreas = std::accumulate(
    AreasOfPolygons_vec.begin(),
    AreasOfPolygons_vec.end(),
    0,
    std::bind(std::plus<double>{}, std::placeholders::_1, std::placeholders::_2));
  return sumOfAreas;
}

double bekhova::getArea(const Polygon& polygon)
{
  std::vector<double> sumOfCoords_vec;
  std::transform(
    polygon.points.begin(),
    std::prev(polygon.points.end()),
    std::next(polygon.points.begin()),
    std::back_inserter(sumOfCoords_vec),
    [](const Point& a, const Point& b)
    {
      return a.x * b.y;
    });

  double sum = std::accumulate(
    sumOfCoords_vec.begin(),
    sumOfCoords_vec.end(),
    0,
    std::bind(std::plus<double>{}, std::placeholders::_1, std::placeholders::_2));

  std::vector<double> diffOfCoords_vec;
  std::transform(
    polygon.points.begin(),
    std::prev(polygon.points.end()),
    std::next(polygon.points.begin()),
    std::back_inserter(diffOfCoords_vec),
    [](const Point& a, const Point& b)
    {
      return a.y * b.x;
    });

  double diff = std::accumulate(
    diffOfCoords_vec.begin(),
    diffOfCoords_vec.end(),
    0,
    std::bind(std::plus<double>{}, std::placeholders::_1, std::placeholders::_2));

  return 0.5 * std::abs(sum + polygon.points.back().x * polygon.points.front().y - diff - polygon.points.front().x * polygon.points.back().y);
}

void bekhova::Max(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::map<std::string, std::function<void(const std::vector<Polygon>& polygons, std::ostream& out)>> maxes;
  maxes["AREA"] = maxArea;
  maxes["VERTEXES"] = maxVertexes;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<COMMAND IS INVALID>\n");
  std::string parameter;
  in >> parameter;
  try
  {
    maxes.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range& ex)
  {
    outInvalid(out);
  }
}

void bekhova::maxArea(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<double> areasOfPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(areasOfPolygons_vec),
    [](const Polygon& polygon)
    {
      return getArea(polygon);
    });
  if (areasOfPolygons_vec.empty())
  {
    throw std::out_of_range("");
  }
  std::sort(areasOfPolygons_vec.begin(), areasOfPolygons_vec.end());
  out << std::setprecision(1) << std::fixed << areasOfPolygons_vec.back() << '\n';
}

void bekhova::maxVertexes(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<std::size_t> vertexesOfPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(vertexesOfPolygons_vec),
    [](const Polygon& polygon)
    {
      return polygon.points.size();
    });
  if (vertexesOfPolygons_vec.empty())
  {
    throw std::out_of_range("");
  }
  std::sort(vertexesOfPolygons_vec.begin(), vertexesOfPolygons_vec.end());
  out << vertexesOfPolygons_vec.back() << '\n';
}

void bekhova::Min(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::map<std::string, std::function<void(const std::vector<Polygon>& polygons, std::ostream& out)>> mines;
  mines["AREA"] = minArea;
  mines["VERTEXES"] = minVertexes;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<COMMAND IS INVALID>\n");
  std::string parameter;
  in >> parameter;
  try
  {
    mines.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range& ex)
  {
    outInvalid(out);
  }
}

void bekhova::minArea(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<double> areasOfPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(areasOfPolygons_vec),
    [](const Polygon& polygon)
    {
      return getArea(polygon);
    });
  if (areasOfPolygons_vec.empty())
  {
    throw std::out_of_range("");
  }
  std::sort(areasOfPolygons_vec.begin(), areasOfPolygons_vec.end());
  out << std::setprecision(1) << std::fixed << areasOfPolygons_vec.front() << '\n';
}

void bekhova::minVertexes(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<std::size_t> vertexesOfPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(vertexesOfPolygons_vec),
    [](const Polygon& polygon)
    {
      return polygon.points.size();
    });
  if (vertexesOfPolygons_vec.empty())
  {
    throw std::out_of_range("");
  }
  std::sort(vertexesOfPolygons_vec.begin(), vertexesOfPolygons_vec.end());
  out << vertexesOfPolygons_vec.front() << '\n';
}

void bekhova::Count(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  std::map<std::string, std::function<void(const std::vector<Polygon>& polygons, std::ostream& out)>> counts;
  counts["EVEN"] = CountEven;
  counts["ODD"] = CountOdd;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<COMMAND IS INVALID>\n");
  std::string parameter;
  in >> parameter;
  try
  {
    counts.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range& ex)
  {
    if (std::isdigit(parameter[0]) && std::stoi(parameter) > 2)
    {
      CountVertexes(std::stoi(parameter), polygons, out);
    }
    else
    {
      outInvalid(out);
    }
  }
}

void bekhova::CountEven(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<std::size_t> EvenPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(EvenPolygons_vec),
    [](const Polygon& polygon)
    {
      return !(polygon.points.size() % 2);
    });
  std::size_t EvenNum = std::accumulate(
    EvenPolygons_vec.begin(),
    EvenPolygons_vec.end(),
    0,
    std::bind(std::plus<std::size_t>{}, std::placeholders::_1, std::placeholders::_2));
  out << EvenNum << '\n';
}

void bekhova::CountOdd(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<std::size_t> OddPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(OddPolygons_vec),
    [](const Polygon& polygon)
    {
      return (polygon.points.size() % 2);
    });
  std::size_t OddNum = std::accumulate(
    OddPolygons_vec.begin(),
    OddPolygons_vec.end(),
    0,
    std::bind(std::plus<std::size_t>{}, std::placeholders::_1, std::placeholders::_2));
  out << OddNum << '\n';
}

void bekhova::CountVertexes(std::size_t vertexes, const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::vector<std::size_t> NVertexesPolygons_vec;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(NVertexesPolygons_vec),
    [vertexes](const Polygon& polygon)
    {
      return polygon.points.size() == vertexes;
    });
  std::size_t NVertexesNum = std::accumulate(
    NVertexesPolygons_vec.begin(),
    NVertexesPolygons_vec.end(),
    0,
    std::bind(std::plus<std::size_t>{}, std::placeholders::_1, std::placeholders::_2));
  out << NVertexesNum << '\n';
}

void bekhova::Perms(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in)
{
  Polygon givenPolygon;
  in >> givenPolygon;
  std::size_t givenPolygonVertexes = givenPolygon.points.size();
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<COMMAND IS INVALID>\n");
  std::vector<Polygon> nVertexes_vec;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(nVertexes_vec),
    [givenPolygonVertexes](const Polygon& polygon)
    {
      return polygon.points.size() == givenPolygonVertexes;
    });
  if (nVertexes_vec.empty())
  {
    outInvalid(out);
  }
  else
  {
    auto comparePolygons = std::bind(checkPerms, givenPolygon, std::placeholders::_1);
    std::size_t count = std::count_if(polygons.begin(), polygons.end(), comparePolygons);
    out << count << '\n';
  }
}

bool bekhova::checkPerms(const Polygon& left, const Polygon& right)
{
  if (left.points.size() != right.points.size())
  {
    return false;
  }
  auto isPointContains = std::bind(checkPoints, left, std::placeholders::_1);
  std::size_t countPointsIn = std::count_if(right.points.begin(), right.points.end(), isPointContains);
  return left.points.size() == countPointsIn;
}

bool bekhova::checkPoints(const Polygon& polygon, const Point& point)
{
  return std::find_if(polygon.points.begin(), polygon.points.end(), [point](const Point& pointToCompare)
    { return (pointToCompare.x == point.x && pointToCompare.y == point.y); }) != polygon.points.end();
}

void bekhova::Rightshapes(const std::vector<Polygon>& polygons, std::ostream& out)
{
  std::size_t count = std::count_if(polygons.begin(), polygons.end(), isRightAngle);
  out << count << '\n';
}

bool bekhova::isRightAngle(const Polygon& polygon)
{
  std::vector<Point> points_vec;
  auto makeVector = std::bind(vectorOnCoords, std::placeholders::_1, std::placeholders::_2);
  std::transform(
    polygon.points.begin(),
    std::prev(polygon.points.end()),
    std::next(polygon.points.begin()),
    std::back_inserter(points_vec),
    makeVector);
  points_vec.push_back(makeVector(polygon.points.back(), polygon.points.front()));
  std::vector<double> cosOfVectors;
  auto getCos = std::bind(cosFromVects, std::placeholders::_1, std::placeholders::_2);
  std::transform(
    points_vec.begin(),
    std::prev(points_vec.end()),
    std::next(points_vec.begin()),
    std::back_inserter(cosOfVectors),
    getCos);
  cosOfVectors.push_back(getCos(points_vec.back(), points_vec.front()));
  return std::find_if(cosOfVectors.begin(), cosOfVectors.end(), [](const double& cos)
    { return cos == 0; }) != cosOfVectors.end();
}

bekhova::Point bekhova::vectorOnCoords(const bekhova::Point& firstPoint, const bekhova::Point& secondPoint)
{
  return bekhova::Point{ secondPoint.x - firstPoint.x, secondPoint.y - firstPoint.y };
}

double bekhova::cosFromVects(const bekhova::Point& firstPoint, const bekhova::Point& secondPoint)
{
  double topExpr = (firstPoint.x * secondPoint.x + firstPoint.y * secondPoint.y);
  double botExprFirst = std::sqrt(std::pow(firstPoint.x, 2) + std::pow(firstPoint.y, 2));
  double botExprSecond = std::sqrt(std::pow(secondPoint.x, 2) + std::pow(secondPoint.y, 2));
  return topExpr / (botExprFirst * botExprSecond);
}

void bekhova::outMessage(std::ostream& out, const std::string& message)
{
  out << message;
}

#include "Commands.hpp"
#include <map>
#include <string>
#include <functional>
#include <numeric>
#include <iomanip>

void semzin::Area(std::vector<Polygon> &polygons, std::ostream &out, std::istream &in)
{
  std::map<std::string, std::function<void(std::vector<Polygon> & polygon, std::ostream & out)>> areas;
  areas["EVEN"] = AreaEven;
  areas["ODD"] = AreaOdd;
  areas["MEAN"] = AreaMean;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string parameter;
  in >> parameter;
  try
  {
    areas.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range &ex)
  {
    if (std::isdigit(parameter[0]))
    {
      AreaVersNum(std::stoi(parameter), polygons, out);
    }
    else
    {
      outInvalid(out);
    }
  }
}

void semzin::AreaEven(std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<Polygon> EvenPolygons_vec;
  std::copy_if(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(EvenPolygons_vec),
      [](Polygon &polygon)
      {
        return !(polygon.points.size() % 2);
      });
  double sum = sumAreas(EvenPolygons_vec);
  out << std::setprecision(1) << sum << '\n';
}

void semzin::AreaOdd(std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<Polygon> OddPolygons_vec;
  std::copy_if(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(OddPolygons_vec),
      [](Polygon &polygon)
      {
        return (polygon.points.size() % 2);
      });
  double sum = sumAreas(OddPolygons_vec);
  out << std::setprecision(1) << sum << '\n';
}

void semzin::AreaMean(std::vector<Polygon> &polygons, std::ostream &out)
{
  if (polygons.empty())
  {
    throw std::out_of_range("");
  }
  double sum = sumAreas(polygons);
  out << std::setprecision(1) << sum / polygons.size() << '\n';
}

void semzin::AreaVersNum(std::size_t vertexes, std::vector<Polygon> &polygons, std::ostream &out)
{
  auto NVertexes = std::bind(std::equal_to<size_t>{}, vertexes, std::placeholders::_1);
  std::vector<Polygon> polygonsWithNVertexes;
  std::copy_if(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(polygonsWithNVertexes),
      [NVertexes](Polygon &polygon)
      {
        return NVertexes(polygon.points.size());
      });

  double sum = sumAreas(polygonsWithNVertexes);
  out << std::setprecision(1) << sum << '\n';
}

double semzin::sumAreas(std::vector<Polygon> &polygons)
{
  std::vector<Polygon> AreasOfPolygons_vec;
  std::transform(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(AreasOfPolygons_vec),
      [](Polygon &polygon)
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

double semzin::getArea(const Polygon &polygon)
{
  std::vector<double> sumOfCoords_vec;
  std::transform(
      polygon.points.begin(),
      std::prev(polygon.points.end()),
      std::next(polygon.points.begin()),
      std::back_inserter(sumOfCoords_vec),
      [](const Point &a, const Point &b)
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
      [](const Point &a, const Point &b)
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

void semzin::Max(std::vector<Polygon> &polygons, std::ostream &out, std::istream &in)
{
  std::map<std::string, std::function<void(std::vector<Polygon> & polygons, std::ostream & out)>> maxes;
  maxes["AREA"] = maxArea;
  maxes["VERTEXES"] = maxVertexes;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string parameter;
  in >> parameter;
  try
  {
    maxes.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range &ex)
  {
    outInvalid(out);
  }
}

void semzin::maxArea(std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<double> areasOfPolygons_vec;
  std::transform(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(areasOfPolygons_vec),
      [](Polygon &polygon)
      {
        return getArea(polygon);
      });
  if (areasOfPolygons_vec.empty())
  {
    throw std::out_of_range("");
  }
  std::sort(areasOfPolygons_vec.begin(), areasOfPolygons_vec.end());
  out << std::setprecision(1) << areasOfPolygons_vec.back() << '\n';
}

void semzin::maxVertexes(std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<std::size_t> vertexesOfPolygons_vec;
  std::transform(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(vertexesOfPolygons_vec),
      [](Polygon &polygon)
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

void semzin::Min(std::vector<Polygon> &polygons, std::ostream &out, std::istream &in)
{
  std::map<std::string, std::function<void(std::vector<Polygon> & polygons, std::ostream & out)>> mines;
  mines["AREA"] = minArea;
  mines["VERTEXES"] = minVertexes;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string parameter;
  in >> parameter;
  try
  {
    mines.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range &ex)
  {
    outInvalid(out);
  }
}

void semzin::minArea(std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<double> areasOfPolygons_vec;
  std::transform(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(areasOfPolygons_vec),
      [](Polygon &polygon)
      {
        return getArea(polygon);
      });
  if (areasOfPolygons_vec.empty())
  {
    throw std::out_of_range("");
  }
  std::sort(areasOfPolygons_vec.begin(), areasOfPolygons_vec.end());
  out << std::setprecision(1) << areasOfPolygons_vec.front() << '\n';
}

void semzin::minVertexes(std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<std::size_t> vertexesOfPolygons_vec;
  std::transform(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(vertexesOfPolygons_vec),
      [](Polygon &polygon)
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

void semzin::Count(std::vector<Polygon> &polygons, std::ostream &out, std::istream &in)
{
  std::map<std::string, std::function<void(std::vector<Polygon> & polygons, std::ostream & out)>> counts;
  counts["EVEN"] = CountEven;
  counts["ODD"] = CountOdd;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string parameter;
  in >> parameter;
  try
  {
    counts.at(parameter)(polygons, out);
  }
  catch (const std::out_of_range &ex)
  {
    if (std::isdigit(parameter[0]))
    {
      CountVertexes(std::stoi(parameter), polygons, out);
    }
    else
    {
      outInvalid(out);
    }
  }
}

void semzin::CountEven(std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<std::size_t> EvenPolygons_vec;
  std::transform(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(EvenPolygons_vec),
      [](Polygon &polygon)
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

void semzin::CountOdd(std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<std::size_t> OddPolygons_vec;
  std::transform(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(OddPolygons_vec),
      [](Polygon &polygon)
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

void semzin::CountVertexes(std::size_t vertexes, std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<std::size_t> NVertexesPolygons_vec;
  std::transform(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(NVertexesPolygons_vec),
      [vertexes](Polygon &polygon)
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

void semzin::outMessage(std::ostream &out, const std::string &message)
{
  out << message;
}

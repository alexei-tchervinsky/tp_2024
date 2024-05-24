#include <functional> //placeholders
#include <algorithm> //min_element, max_element, transform, remove_if, count_if
#include <numeric> //accumulate
#include <cmath> //pow sqrt

#include "command.hpp"

using namespace kladkovoj;
using namespace command;
using namespace std::placeholders;

int command::isInputNumber(const std::string &num)
{
  char *end;
  int res = strtol(num.c_str(), &end, 10);

  if(*end != 0)
    return -1;
  return res;
}

bool command::isRectangle(const Polygon &poly)
{
  if (poly.points.size() != 4)
  {
    return false;
  }

  auto distanceSquared = []
  (const Point& a, const Point& b)
  {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return std::pow(dx, 2) + std::pow(dy, 2);
  };

  auto dotProduct = []
  (const Point& a, const Point& b, const Point& c)
  {
    double abx = b.x - a.x;
    double aby = b.y - a.y;
    double bcx = c.x - b.x;
    double bcy = c.y - b.y;
    return abx * bcx + aby * bcy;
  };

  double d2 = distanceSquared(poly.points[0], poly.points[1]);
  double d3 = distanceSquared(poly.points[1], poly.points[2]);
  double d4 = distanceSquared(poly.points[2], poly.points[3]);
  double d1 = distanceSquared(poly.points[3], poly.points[0]);

  double diag1 = distanceSquared(poly.points[0], poly.points[2]);
  double diag2 = distanceSquared(poly.points[1], poly.points[3]);

  return d1 == d3 && d2 == d4 && diag1 == diag2 && dotProduct(poly.points[0], poly.points[1], poly.points[2]) == 0;
}

void command::area(const std::vector<Polygon>& data)
{
  std::string arg;
  int num;

  std::cin >> arg;
  num = isInputNumber(arg);

  auto cntFunc = [num]
  (double ac, const Polygon& el, int div, int rest)
  {
    double res = ac;

    if(el.points.size() % div == static_cast<size_t>(rest) || rest == -1)
      res += el.area();
    return res;
  };

  if (num == -1)
  {
    if (arg == "EVEN")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0, std::bind(cntFunc, _1, _2, 2, 0)) << std::endl;
    }
    else if (arg == "ODD")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0, std::bind(cntFunc, _1, _2, 2, 1)) << std::endl;
    }
    else if(arg == "MEAN" && data.size() != 0)
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0, std::bind(cntFunc, _1, _2, 2, -1)) / data.size() << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }
  else if(num > 2)
  {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0, std::bind(cntFunc, _1, _2, 0x7FFFFFFF, num)) / data.size() << std::endl;
  }
  else
  {
    throw "<INVALID COMMAND>";
  }
}

void command::min(const std::vector<Polygon>& data)
{
  std::string arg;
  std::cin >> arg;

  if (data.size() == 0)
    throw "<INVALID COMMAND>";

  std::vector<size_t> sizeVec(data.size());

  std::transform(data.begin(), data.end(), sizeVec.begin(), [](const Polygon &poly) {return poly.points.size(); });
  auto poly = std::min_element(data.begin(), data.end());
  auto minSize = std::min_element(sizeVec.begin(), sizeVec.end());

  if (arg == "AREA")
    std::cout << poly->area() << std::endl;
  else if(arg == "VERTEXES")
    std::cout << *minSize << std::endl;
  else
    throw "<INVALID COMMAND>";
}

void command::max(const std::vector<Polygon>& data)
{
  std::string arg;
  std::cin >> arg;

  if (data.size() == 0)
    throw "<INVALID COMMAND>";

  std::vector<size_t> sizeVec(data.size());

  std::transform(data.begin(), data.end(), sizeVec.begin(), [](const Polygon &poly) {return poly.points.size(); });
  auto poly = std::max_element(data.begin(), data.end());
  auto maxSize = std::max_element(sizeVec.begin(), sizeVec.end());

  if (arg == "AREA")
    std::cout << poly->area() << std::endl;
  else if(arg == "VERTEXES")
    std::cout << *maxSize << std::endl;
  else
    throw "<INVALID COMMAND>";
}

void command::count(const std::vector<Polygon>& data)
{
  std::string arg;
  int num;

  std::cin >> arg;

  num = isInputNumber(arg);

  auto cntFunc = [num]
  (const Polygon &el, int div, int rest)
  {
    return (el.points.size() % div == static_cast<size_t>(rest) || rest == -1);
  };

  if(num == -1)
  {
    if (arg == "EVEN")
    {
      std::cout << std::count_if(data.begin(), data.end(), std::bind(cntFunc, _1, 2, 0)) << std::endl;
    }
    else if(arg == "ODD")
    {
      std::cout << std::count_if(data.begin(), data.end(), std::bind(cntFunc, _1, 2, 1)) << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }
  else if(num > 2)
  {
    std::cout << std::count_if(data.begin(), data.end(), std::bind(cntFunc, _1, 0x7FFFFFFF, num)) << std::endl;
  }
  else
  {
    throw "<INVALID COMMAND>";
  }
}

void command::rects(const std::vector<Polygon>& data)
{
  std::cout << std::count_if(data.begin(), data.end(), isRectangle);
}

void command::intersections(const std::vector<Polygon>& data)
{
  Polygon arg;

  std::cin >> arg;

  int ch = std::cin.get();

  while (ch != int('\n') && ch != EOF)
  {
    if (!isspace(ch))
    {
      std::cin.setstate(std::istream::failbit);
      break;
    }
    ch = std::cin.get();
  }

  if (!std::cin)
  {
    std::cin.clear();
    throw "<INVALID COMMAND>";
  }

  auto cntFunc = [&arg]
  (const Polygon& poly)
  {
    return poly.isIntersect(arg);
  };

  std::cout << std::count_if(data.begin(), data.end(), cntFunc) << std::endl;
}
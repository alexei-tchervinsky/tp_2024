#include "commands.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <string>
#include <numeric>
#include <functional>

void evstigneev::area(const std::vector<evstigneev::Polygon>& poly, std::istream& in, std::ostream& out)
{
  enum ModType {EVEN, ODD, NUM, MEAN};
  auto area_if = [](double ac, const evstigneev::Polygon& poly,
    std::size_t vexes, ModType m)
  {
    if ((m == EVEN && poly.points.size() % 2 == 0) ||
      (m == ODD && poly.points.size() % 2 == 1) ||
      (m == NUM && poly.points.size() == vexes) ||
      (m == MEAN))
    {
      ac += poly.getArea();
    }
    return ac;
  };
  std::string cmd;
  in >> cmd;
  if (cmd == "ODD")
  {
    out << std::accumulate(poly.begin(), poly.end(),
      0.0, std::bind(area_if, std::placeholders::_1,
        std::placeholders::_2, 0, ODD)) << '\n';
  }
  else if (cmd == "EVEN")
  {
    out << std::accumulate(poly.begin(), poly.end(),
      0.0, std::bind(area_if, std::placeholders::_1,
        std::placeholders::_2, 0, EVEN)) << '\n';
  }
  else if (cmd == "MEAN" && poly.size() != 0)
  {
    out << std::accumulate(poly.begin(), poly.end(),
      0.0, std::bind(area_if, std::placeholders::_1,
        std::placeholders::_2, 0, MEAN)) / poly.size() << '\n';
  }
  else if (std::all_of(cmd.begin(), cmd.end(), isdigit) && stoi(cmd) > 2)
  {
    out << std::accumulate(poly.begin(), poly.end(),
      0.0, std::bind(area_if, std::placeholders::_1,
        std::placeholders::_2, stoi(cmd), NUM)) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void evstigneev::max(const std::vector<evstigneev::Polygon>& poly, std::istream& in, std::ostream& out)
{
  std::string cmd;
  in >> cmd;

  if (poly.empty())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }

  if (cmd == "AREA")
  {
    out << std::max_element(poly.begin(), poly.end())->getArea() << '\n';
  }
  else if (cmd == "VERTEXES")
  {
    out << std::accumulate(poly.begin() + 1, poly.end(),
      poly[0].points.size(), [](std::size_t max_i, const Polygon& poly)
      {
        if (poly.points.size() > max_i)
        {
          return poly.points.size();
        }
        else
        {
          return max_i;
        }
      }) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void evstigneev::min(const std::vector<evstigneev::Polygon>& poly, std::istream& in, std::ostream& out)
{
  std::string cmd;
  in >> cmd;

  if (poly.empty())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }

  if (cmd == "AREA")
  {
    out << std::min_element(poly.begin(), poly.end())->getArea() << '\n';
  }
  else if (cmd == "VERTEXES")
  {
    out << std::accumulate(poly.begin() + 1, poly.end(),
      poly[0].points.size(), [](std::size_t min_i, const Polygon& poly)
      {
        if (poly.points.size() < min_i)
        {
          return poly.points.size();
        }
        else
        {
          return min_i;
        }
      }) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void evstigneev::count(const std::vector<Polygon>& poly, std::istream& in, std::ostream& out)
{
  std::string cmd;
  in >> cmd;
  try
  {
    if (cmd == "ODD")
    {
      out << std::setprecision(0) << count_(1, poly) << '\n';
    }
    else if (cmd == "EVEN")
    {
      out << std::setprecision(0) << count_(2, poly) << '\n';
    }
    else if (stoll(cmd) >= 3)
    {
      out << std::setprecision(0) << count_(stoll(cmd), poly) << '\n';
    }
    else
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
  }
  catch (std::exception& ex)
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void evstigneev::lessArea(const std::vector<evstigneev::Polygon>& poly, std::istream& in, std::ostream& out)
{
  if (poly.empty())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  Polygon p1, p2;
  in >> p2;
  if (!in || in.peek() != '\n')
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  auto lss = [&p1](const Polygon& p2)
  {
    bool r = p1.getArea() > p2.getArea();
    return r;
  };
  out << std::count_if(poly.begin(), poly.end(), lss) << '\n';
}

void evstigneev::mxSeq(const std::vector<evstigneev::Polygon>& poly, std::istream& in, std::ostream& out)
{
  Polygon p;
  in >> p;
  if (!in || in.peek() != '\n')
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  out << std::setprecision(0) << seq(poly.cbegin(), poly.cend(), p) << '\n';
}

std::size_t evstigneev::seq(std::vector<Polygon>::const_iterator begin,
  std::vector<Polygon>::const_iterator end, const Polygon& param)
{
  bool repeat = true;
  std::function<bool(const Polygon&)> find = std::bind([](const Polygon& polygon, const Polygon& param)
    {
      return (polygon == param);
    }, std::placeholders::_1, param);
  std::function<bool(const Polygon&)> count = std::bind([](const Polygon& polygon, const Polygon& param, bool& repeat)
    {
      if (polygon == param && repeat == true)
      {
        return true;
      }
      repeat = false;
      return false;
    }, std::placeholders::_1, param, repeat);
  std::vector<evstigneev::Polygon >::const_iterator begin_new = std::find_if(begin, end, find);
  if (begin_new != end)
  {
    std::size_t count_current = std::count_if(begin_new, end, count);
    std::size_t count_next = seq(begin_new + count_current, end, param);
    if (count_current > count_next)
    {
      return count_current;
    }
    return count_next;
  }
  else
  {
    return 0;
  }
}

std::size_t evstigneev::count_(std::size_t param, const std::vector<Polygon> polygons)
{
  auto isValidPolygon = [](const Polygon& poly)
  {
    return poly.points.size() >= 3 &&
      std::all_of(poly.points.cbegin(), poly.points.cend(), [](const Point& pt)
      {
        return pt.x != -1 && pt.y != -1;
      });
  };
  if (param == 1)
  {
    return std::count_if(polygons.cbegin(), polygons.cend(),
      [isValidPolygon](const Polygon& a)
      {
        return isValidPolygon(a) && a.points.size() % 2 != 0;
      });
  }
  else if (param == 2)
  {
    return std::count_if(polygons.cbegin(), polygons.cend(),
      [isValidPolygon](const Polygon& a)
      {
        return isValidPolygon(a) && a.points.size() % 2 == 0;
      });
  }
  std::function<std::size_t(const Polygon&)> UOp =
    std::bind([](const Polygon& a, std::size_t param, std::function<bool(const Polygon&)> isValidPolygon)
    {
      return isValidPolygon(a) && a.points.size() == param;
    },
    std::placeholders::_1,
    param,
      isValidPolygon);
  return std::count_if(polygons.cbegin(), polygons.cend(), UOp);
}

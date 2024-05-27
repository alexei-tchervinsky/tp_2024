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
        std::placeholders::_2, 0, ODD)) << "\n";
  }
  else if (cmd == "EVEN")
  {
    out << std::accumulate(poly.begin(), poly.end(),
      0.0, std::bind(area_if, std::placeholders::_1,
        std::placeholders::_2, 0, EVEN)) << "\n";
  }
  else if (cmd == "MEAN" && poly.size() != 0)
  {
    out << std::accumulate(poly.begin(), poly.end(),
      0.0, std::bind(area_if, std::placeholders::_1,
        std::placeholders::_2, 0, MEAN)) / poly.size() << "\n";
  }
  else if (std::all_of(cmd.begin(), cmd.end(), isdigit) && stoi(cmd) > 2)
  {
    out << std::accumulate(poly.begin(), poly.end(),
      0.0, std::bind(area_if, std::placeholders::_1,
        std::placeholders::_2, stoi(cmd), NUM)) << "\n";
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
    out << std::max_element(poly.begin(), poly.end())->getArea() << "\n";
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
      }) << "\n";
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
    out << std::min_element(poly.begin(), poly.end())->getArea() << "\n";
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
      }) << "\n";
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void evstigneev::count(const std::vector<evstigneev::Polygon>& poly, std::istream& in, std::ostream& out)
{
  std::string cmd;
  in >> cmd;

  if (cmd == "ODD")
  {
    out << std::count_if(poly.begin(), poly.end(),
      [](const Polygon& p)
      {
        return p.points.size() % 2 == 1;
      }) << "\n";
  }
  else if (cmd == "EVEN")
  {
    out << std::count_if(poly.begin(), poly.end(),
      [](const Polygon& p)
      {
        return p.points.size() % 2 == 0;
      }) << "\n";
  }
  else if (std::all_of(cmd.begin(), cmd.end(), isdigit) && stoi(cmd) > 2)
  {
    std::size_t vexes = stoi(cmd);
    out << std::count_if(poly.begin(), poly.end(),
      [&vexes](const Polygon& p)
      {
        return p.points.size() == vexes;
      }) << "\n";
  }
  else
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
  if (!std::cin)
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  auto lss = [&p1](const Polygon& p2)
  {
    return p1.getArea() > p2.getArea();
  };
  out << std::count_if(poly.begin(), poly.end(), lss) << "\n";
}

void evstigneev::mxSeq(const std::vector<evstigneev::Polygon>& poly, std::istream& in, std::ostream& out)
{
  if (poly.empty())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  size_t numOfVexes = 0, counter = 0;
  std::vector<Point> srcPoints;
  std::vector<size_t> seques;

  auto isEqualCount = [](const Polygon& poly,
    const std::vector<Point>& src, size_t& c)
  {
    if (src == poly.points)
    {
      c++;
    }
    else
    {
      c = 0;
    }
    return c;
  };

  using in_it = std::istream_iterator<Point>;
  in >> numOfVexes;

  if (numOfVexes < 3)
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }

  std::copy_n(in_it{ std::cin }, numOfVexes, std::back_inserter(srcPoints));

  if (srcPoints.empty())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }

  using namespace std::placeholders;
  auto f = std::bind(isEqualCount, _1, srcPoints, counter);
  std::transform(poly.begin(), poly.end(),
    std::back_inserter(seques), f);

  auto mx = std::max_element(seques.begin(), seques.end());

  out << *mx << "\n";
}
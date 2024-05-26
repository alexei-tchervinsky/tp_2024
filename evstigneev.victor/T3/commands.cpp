#include "commands.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <numeric>
#include <functional>

void evstigneev::area(const std::vector<evstigneev::Polygon>& poly)
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
  std::cin >> cmd;
  if (cmd == "ODD")
  {
    std::cout << std::accumulate(poly.begin(), poly.end(),
      0.0, std::bind(area_if, std::placeholders::_1,
        std::placeholders::_2, 0, ODD)) << "\n";
  }
  else if (cmd == "EVEN")
  {
    std::cout << std::accumulate(poly.begin(), poly.end(),
      0.0, std::bind(area_if, std::placeholders::_1,
        std::placeholders::_2, 0, EVEN)) << "\n";
  }
  else if (cmd == "MEAN" && poly.size() != 0)
  {
    std::cout << std::accumulate(poly.begin(), poly.end(),
      0.0, std::bind(area_if, std::placeholders::_1,
        std::placeholders::_2, 0, MEAN)) / poly.size() << "\n";
  }
  else if (std::all_of(cmd.begin(), cmd.end(), isdigit) && stoi(cmd) > 2)
  {
    std::cout << std::accumulate(poly.begin(), poly.end(),
      0.0, std::bind(area_if, std::placeholders::_1,
        std::placeholders::_2, stoi(cmd), NUM)) << "\n";
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void evstigneev::max(const std::vector<evstigneev::Polygon>& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::string cmd;
  std::cin >> cmd;
  if (cmd == "AREA")
  {
    std::cout << std::max_element(poly.begin(), poly.end())->getArea() << "\n";
  }
  else if (cmd == "VERTEXES")
  {
    std::cout << std::accumulate(poly.begin() + 1, poly.end(),
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
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void evstigneev::min(const std::vector<evstigneev::Polygon>& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::string cmd;
  std::cin >> cmd;
  if (cmd == "AREA")
  {
    std::cout << std::min_element(poly.begin(), poly.end())->getArea() << "\n";
  }
  else if (cmd == "VERTEXES")
  {
    std::cout << std::accumulate(poly.begin() + 1, poly.end(),
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
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void evstigneev::count(const std::vector<evstigneev::Polygon>& poly)
{
  enum ModType { EVEN, ODD, NUM };
  auto c_if = [](const evstigneev::Polygon& poly,
    std::size_t vexes, ModType m)
  {
    return ((m == EVEN && poly.points.size() % 2 == 0) ||
      (m == ODD && poly.points.size() % 2 == 1) ||
      (m == NUM && poly.points.size() == vexes));
  };
  std::string cmd;
  std::cin >> cmd;
  if (cmd == "ODD")
  {
    std::cout << std::count_if(poly.begin(), poly.end(),
      std::bind(c_if, std::placeholders::_1,
        0, ODD)) << "\n";
  }
  else if (cmd == "EVEN")
  {
    std::cout << std::count_if(poly.begin(), poly.end(),
      std::bind(c_if, std::placeholders::_1,
        0, EVEN)) << "\n";
  }
  else if (std::all_of(cmd.begin(), cmd.end(), isdigit) && stoi(cmd) > 2)
  {
    std::cout << std::count_if(poly.begin(), poly.end(),
      std::bind(c_if, std::placeholders::_1,
        0, stoi(cmd))) << "\n";
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void evstigneev::lessArea(const std::vector<evstigneev::Polygon>& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  Polygon p1, p2;
  if (!std::cin)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto lss = [&p1](const Polygon& p2)
  {
    return p1.getArea() > p2.getArea();
  };
  std::cout << std::count_if(poly.begin(), poly.end(), lss) << "\n";
}

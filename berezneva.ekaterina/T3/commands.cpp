#include "commands.h"

using namespace std::placeholders;

void berezneva::area(const std::vector<Polygon> &data)
{
  auto accumalateArea_if = [](double ac, const berezneva::Polygon &poly, std::size_t mod2, std::size_t vertices)
  {
    if ((poly.points_.size() % 2 == mod2) || (mod2 == 2 && poly.points_.size() == vertices) || (mod2 == 3))
    {
      ac += poly.getArea();
    }
    return ac;
  };

  std::string arg;
  std::cin >> arg;
  if (arg == "EVEN")
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                 std::bind(accumalateArea_if, _1, _2, 0, 0)) << '\n';
  }
  else if (arg == "ODD")
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                 std::bind(accumalateArea_if, _1, _2, 1, 0)) << '\n';
  }
  else if (arg == "MEAN" && data.size() != 0)
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                  std::bind(accumalateArea_if, _1, _2, 3, 0)) / data.size() << std::endl;
  }
  else if (std::all_of(arg.begin(), arg.end(), isdigit) && stoi(arg) > 2)
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                 std::bind(accumalateArea_if, _1, _2, 2, stoi(arg))) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void berezneva::min(const std::vector<Polygon> &data)
{
  if (data.empty())
    throw std::runtime_error("<INVALID COMMAND>");

  std::string arg;
  std::cin >> arg;

  if (arg == "AREA")
  {
    std::cout << std::min_element(data.begin(), data.end())->getArea() << '\n';
  }
  else if (arg == "VERTEXES")
  {
    std::vector<std::size_t> sizes(data.size());

    std::cout << std::accumulate(
            data.begin() + 1,
            data.end(),
            data[0].points_.size(),
            [](std::size_t min, const Polygon &poly )
            {
              return (poly.points_.size() < min ? poly.points_.size() : min);
            }
        ) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void berezneva::max(const std::vector<Polygon> &data)
{
  if (data.empty())
    throw std::runtime_error("<INVALID COMMAND>");

  std::string arg;
  std::cin >> arg;

  if (arg == "AREA")
  {
    std::cout << std::max_element(data.begin(), data.end())->getArea() << '\n';
  }
  else if (arg == "VERTEXES")
  {
    std::vector<std::size_t> sizes(data.size());

    std::cout << std::accumulate(
            data.begin() + 1,
            data.end(),
            data[0].points_.size(),
            [](std::size_t max, const Polygon &poly )
            {
              return (poly.points_.size() > max ? poly.points_.size() : max);
            }
        ) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void berezneva::count(const std::vector<Polygon> &data)
{
  auto countPolygons_if = [](const berezneva::Polygon &poly, std::size_t mod2, std::size_t vertices)
      {
        return ((poly.points_.size() % 2 == mod2) || (mod2 == 2 && poly.points_.size() == vertices));
      };

  std::string arg;
  std::cin >> arg;
  if (arg == "EVEN")
  {
    std::cout << std::count_if(data.begin(), data.end(),
                 std::bind(countPolygons_if, _1, 0, 0)) << '\n';
  }
  else if (arg == "ODD")
  {
    std::cout << std::count_if(data.begin(), data.end(),
                 std::bind(countPolygons_if, _1, 1, 0)) << '\n';
  }
  else if (std::all_of(arg.begin(), arg.end(), isdigit) && stoi(arg) > 2)
  {
    std::cout << std::count_if(data.begin(), data.end(),
                 std::bind(countPolygons_if, _1, 2, stoi(arg))) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void berezneva::lessArea(std::vector<Polygon> &value)
{
  if (value.empty())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }

  Polygon mainEl, otherEl;
  std::cin >> otherEl;
  if (std::cin.fail() || std::cin.get() != '\n')
    throw std::runtime_error("<INVALID COMMAND>");

  auto calcConcur = [&mainEl](const Polygon &otherEl)
    {
      bool rez = mainEl.getArea() > otherEl.getArea();
      return rez;
    };
  std::cout << std::count_if(value.begin(), value.end(), calcConcur) << "\n";

}

void berezneva::intersect(const std::vector<Polygon> &value)
{
  if (value.empty())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }

  Polygon mainEl, otherEl;
  std::cin >> mainEl;
  if (std::cin.fail() || std::cin.get() != '\n')
    throw std::runtime_error("<INVALID COMMAND>");

  auto calcConcur = [&mainEl](const Polygon &otherEl)
    {
      return mainEl.isIntersect(otherEl);
    };
  std::cout << std::count_if(value.begin(), value.end(), calcConcur) << "\n";
}


#include "Commands.hpp"
#include <numeric>
#include <functional>
#include <algorithm>
#include <cmath>

namespace ananev
{
  void error(std::istream &in)
  {
    std::cerr << "<INVALID COMMAND>\n";
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  double get_sum(double result, const Polygon& polygon, std::size_t param)
  {
    if (param == 0)
    {
      return result + area(polygon);
    }
    else if (param == 1 && polygon.points.size() % 2 != 0)
    {
      return result + area(polygon);
    }
    else if (param == 2 && polygon.points.size() % 2 == 0)
    {
      return result + area(polygon);
    }
    else if (param == polygon.points.size())
    {
      return result + area(polygon);
    }
    return result;
  }

  double get_area(std::size_t param, const std::vector< ananev::Polygon > polygons)
  {
    std::function< double(double, const Polygon&) > BinaryOperation = std::bind(get_sum, std::placeholders::_1, std::placeholders::_2, param);
    if (param == 0)
    {
        return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, BinaryOperation) / polygons.size();
    }
    return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, BinaryOperation);
  }

  double get_max(std::size_t param, const std::vector< ananev::Polygon > polygons)
  {
    if (param == 0)
    {
      return area(*std::max_element(polygons.cbegin(), polygons.cend(), [](const Polygon& a, const Polygon& b)
      {
        return area(a) < area(b);
      }));
    }
    return std::max_element(polygons.cbegin(), polygons.cend(), [](const Polygon& a, const Polygon& b)
      {
        return a.points.size() < b.points.size();
      })->points.size();
  }

  double get_min(std::size_t param, const std::vector< ananev::Polygon > polygons)
  {
    if (param == 0)
    {
      return area(*std::min_element(polygons.cbegin(), polygons.cend(), [](const Polygon& a, const Polygon& b)
      {
        return area(a) < area(b);
      }));
    }
    return std::min_element(polygons.cbegin(), polygons.cend(), [](const Polygon& a, const Polygon& b)
      {
        return a.points.size() < b.points.size();
      })->points.size();
  }

  std::size_t get_count(std::size_t param, const std::vector< ananev::Polygon > polygons)
  {
    if (param == 1)
    {
      return std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon& a)
      {
        return a.points.size() % 2 != 0;
      });
    }
    else if (param == 2)
    {
      return std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon& a)
      {
        return a.points.size() % 2 == 0;
      });
    }
    std::function< std::size_t(const Polygon&) > UnarOperation = std::bind([](const Polygon& a, std::size_t param) {return a.points.size() == param;}, std::placeholders::_1, param);
    return std::count_if(polygons.cbegin(), polygons.cend(), UnarOperation);
  }

  std::size_t get_rects(const std::vector< ananev::Polygon > polygons)
  {
    return 0;
  }

  std::size_t get_maxseq(const Polygon polygon, const std::vector< ananev::Polygon > polygons)
  {
    return 0;
  }

  void area_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out)
  {
    std::string param;
    in >> param;
    try
    {
      if (param == "MEAN" && polygons.size() >= 1)
      {
        out << get_area(0, polygons) << '\n';
      }
      else if (param == "ODD")
      {
        out << get_area(1, polygons) << '\n';
      }
      else if (param == "EVEN")
      {
        out << get_area(2, polygons) << '\n';
      }
      else if (stoll(param) >= 3)
      {
        out << get_area(stoll(param), polygons)<< '\n';
      }
      else
      {
        error(in);
      }
    }
    catch(std::exception& ex)
    {
      error(in);
    }
  }

  void max_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out)
  {
    std::string param;
    in >> param;
    if (param == "AREA" && polygons.size() >= 1)
    {
      out << get_max(0, polygons) << '\n';
    }
    else if (param == "VERTEXES" && polygons.size() >= 1)
    {
      out << round(get_max(1, polygons)) << '\n';
    }
    else
    {
      error(in);
    }
  }

  void min_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out)
  {
    std::string param;
    in >> param;
    if (param == "AREA" && polygons.size() >= 1)
    {
      out << get_min(0, polygons) << '\n';
    }
    else if (param == "VERTEXES" && polygons.size() >= 1)
    {
      out << round(get_min(1, polygons)) << '\n';
    }
    else
    {
      error(in);
    }
  }

  void count_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out)
  {
    std::string param;
    in >> param;
    try
    {
      if (param == "ODD")
      {
        out << get_count(1, polygons) << '\n';
      }
      else if (param == "EVEN")
      {
        out << get_count(2, polygons) << '\n';
      }
      else if (stoll(param) >= 3)
      {
        out << get_count(stoll(param), polygons) << '\n';
      }
      else
      {
        error(in);
      }
    }
    catch (std::exception& ex)
    {
      error(in);
    }
  }

  void rects_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out)
  {
  }

  void maxseq_param(const std::vector< ananev::Polygon > polygons, std::istream &in, std::ostream &out)
  {
  }
}
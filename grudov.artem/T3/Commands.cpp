#include "Commands.h"


namespace grudov
{
  double areaPolygon(const Polygon& polygon)
  {
    double area = 0;
    std::size_t count_points = polygon.points_.size();
    for (std::size_t point = 0; point < count_points; point++)
    {
      if (point == count_points -1)
      {
        area += (polygon.points_[point].x_ * polygon.points_[0].y_ - polygon.points_[point].y_ *
        polygon.points_[0].x_);
      }
      else
      {
        area += (polygon.points_[point].x_ * polygon.points_[point+1].y_ - polygon.points_[point].y_ *
        polygon.points_[point+1].x_);
      }
    }
    return 0.5*abs(area);
  }
  double get_sum(double result, const Polygon& polygon, std::size_t arg)
  {
    if (arg == 0)
    {
      return result + areaPolygon(polygon);
    }
    else if (arg == 1 && polygon.points_.size() % 2 != 0)
    {
      return result + areaPolygon(polygon);
    }
    else if (arg == 2 && polygon.points_.size() % 2 == 0)
    {
      return result + areaPolygon(polygon);
    }
    else if (arg == polygon.points_.size())
    {
      return result + areaPolygon(polygon);
    }
    return result;
  }

  double get_area(std::size_t arg, const std::vector< grudov::Polygon > polygons)
  {
    std::function< double(double, const Polygon&) > BinaryOperation = std::bind(get_sum,
    std::placeholders::_1,
    std::placeholders::_2,
    arg);
    if (arg == 0)
    {
        return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, BinaryOperation) / polygons.size();
    }
    return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, BinaryOperation);
  }

  double get_max(std::size_t arg, const std::vector< grudov::Polygon > polygons)
  {
    if (arg == 0)
    {
      return areaPolygon(*std::max_element(polygons.cbegin(), polygons.cend(), [](const Polygon& a, const Polygon& b)
      {
        return areaPolygon(a) < areaPolygon(b);
      }));
    }
    return std::max_element(polygons.cbegin(), polygons.cend(), [](const Polygon& a, const Polygon& b)
      {
        return a.points_.size() < b.points_.size();
      })->points_.size();
  }

  double get_min(std::size_t arg, const std::vector< grudov::Polygon > polygons)
  {
    if (arg == 0)
    {
      return areaPolygon(*std::min_element(polygons.cbegin(), polygons.cend(), [](const Polygon& a, const Polygon& b)
      {
        return areaPolygon(a) < areaPolygon(b);
      }));
    }
    return std::min_element(polygons.cbegin(), polygons.cend(), [](const Polygon& a, const Polygon& b)
      {
        return a.points_.size() < b.points_.size();
      })->points_.size();
  }

  std::size_t get_count(std::size_t arg, const std::vector< grudov::Polygon > polygons)
  {
    if (arg == 1)
    {
      return std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon& a)
      {
        return a.points_.size() % 2 != 0;
      });
    }
    else if (arg == 2)
    {
      return std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon& a)
      {
        return a.points_.size() % 2 == 0;
      });
    }
    std::function< std::size_t(const Polygon&) > UnarOperation = std::bind([](const Polygon& a, std::size_t arg)
    {
      return a.points_.size() == arg;
    },
    std::placeholders::_1,
    arg);
    return std::count_if(polygons.cbegin(), polygons.cend(), UnarOperation);
  }

  bool get_rects(const Point& start, const Point& end1, const Point& end2, const Point& end3)
  {
    Point vectors[3];
    vectors[0].x_ = end1.x_-start.x_;
    vectors[0].y_ = end1.y_-start.y_;
    vectors[1].x_ = end2.x_-start.x_;
    vectors[1].y_ = end2.y_-start.y_;
    vectors[2].x_ = end3.x_-start.x_;
    vectors[2].y_ = end3.y_-start.y_;
    bool angle01 = ((vectors[0].x_*vectors[1].x_+vectors[0].y_*vectors[1].y_)/
    (sqrt(std::pow(vectors[0].x_, 2)+std::pow(vectors[0].y_, 2))*sqrt(std::pow(vectors[1].x_, 2)+std::pow(vectors[1].y_, 2))) == 0);
    bool angle02 = ((vectors[0].x_*vectors[2].x_+vectors[0].y_*vectors[2].y_)/
    (sqrt(std::pow(vectors[0].x_, 2)+std::pow(vectors[0].y_, 2))*sqrt(std::pow(vectors[2].x_, 2)+std::pow(vectors[2].y_, 2))) == 0);
    bool angle12 = ((vectors[2].x_*vectors[1].x_+vectors[2].y_*vectors[1].y_)/
    (sqrt(std::pow(vectors[2].x_, 2)+std::pow(vectors[2].y_, 2))*sqrt(std::pow(vectors[1].x_, 2)+std::pow(vectors[1].y_, 2))) == 0);
    return angle01 || angle02 || angle12;
  }
  std::size_t get_seq(std::vector< grudov::Polygon >::const_iterator begin,
  std::vector< grudov::Polygon >::const_iterator end, const Polygon& arg)
  {
    bool repeat = true;
    std::function<bool(const Polygon&)> FindIfUO = std::bind([](const Polygon& polygon, const Polygon& arg)
    {
      return (polygon == arg);
    }, std::placeholders::_1, arg);
    std::function<bool(const Polygon&)> CountIfUO = std::bind([](const Polygon& polygon, const Polygon& arg, bool& repeat)
    {
      if (polygon == arg && repeat == true)
      {
        return true;
      }
      repeat = false;
      return false;
    }, std::placeholders::_1, arg, repeat);
    std::vector< grudov::Polygon >::const_iterator begin_new = std::find_if(begin, end, FindIfUO);
    if (begin_new != end)
    {
      std::size_t count_current = std::count_if(begin_new, end, CountIfUO);
      std::size_t count_next = get_seq(begin_new + count_current, end, arg);
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

  void area(const std::vector< grudov::Polygon > polygons, std::istream &in, std::ostream &out)
  {
    std::string arg;
    in >> arg;
    try
    {
      if (arg == "MEAN" && polygons.size() >= 1)
      {
        out << std::setprecision(1) << get_area(0, polygons) << '\n';
      }
      else if (arg == "ODD")
      {
        out << std::setprecision(1) << get_area(1, polygons) << '\n';
      }
      else if (arg == "EVEN")
      {
        out << std::setprecision(1) << get_area(2, polygons) << '\n';
      }
      else if (stoll(arg) >= 3)
      {
        out << std::setprecision(1) << get_area(stoll(arg), polygons)<< '\n';
      }
      else
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
    catch(std::exception& ex)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }

  void max(const std::vector< grudov::Polygon > polygons, std::istream &in, std::ostream &out)
  {
    std::string arg;
    in >> arg;
    if (arg == "AREA" && polygons.size() >= 1)
    {
      out << std::setprecision(1) << get_max(0, polygons) << '\n';
    }
    else if (arg == "VERTEXES" && polygons.size() >= 1)
    {
      out << std::setprecision(0) << get_max(1, polygons) << '\n';
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }

  void min(const std::vector< grudov::Polygon > polygons, std::istream &in, std::ostream &out)
  {
    std::string arg;
    in >> arg;
    if (arg == "AREA" && polygons.size() >= 1)
    {
      out << std::setprecision(1) << get_min(0, polygons) << '\n';
    }
    else if (arg == "VERTEXES" && polygons.size() >= 1)
    {
      out << std::setprecision(0) << get_min(1, polygons) << '\n';
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }

  void count(const std::vector< grudov::Polygon > polygons, std::istream &in, std::ostream &out)
  {
    std::string arg;
    in >> arg;
    try
    {
      if (arg == "ODD")
      {
        out << std::setprecision(0) << get_count(1, polygons) << '\n';
      }
      else if (arg == "EVEN")
      {
        out << std::setprecision(0) << get_count(2, polygons) << '\n';
      }
      else if (stoll(arg) >= 3)
      {
        out << std::setprecision(0) << get_count(stoll(arg), polygons) << '\n';
      }
      else
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
    catch (std::exception& ex)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }

  void rects(const std::vector< grudov::Polygon > polygons, std::istream &in, std::ostream &out)
  {
    if (!in)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    out << std::setprecision(0) << std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon& polygon)
    {
      if (polygon.points_.size()==4)
      {
        return get_rects(polygon.points_[0], polygon.points_[1], polygon.points_[2], polygon.points_[3]) &&
        get_rects(polygon.points_[1], polygon.points_[2], polygon.points_[3], polygon.points_[0]) &&
        get_rects(polygon.points_[2], polygon.points_[3], polygon.points_[0], polygon.points_[1]);
      }
      return false;
    }) << '\n';
  }

  void maxseq(const std::vector< grudov::Polygon > polygons, std::istream &in, std::ostream &out)
  {
    Polygon arg;
    in >> arg;
    if (!in || in.peek() != '\n')
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    out << std::setprecision(0) << get_seq(polygons.cbegin(), polygons.cend(), arg) << '\n';
  }
}

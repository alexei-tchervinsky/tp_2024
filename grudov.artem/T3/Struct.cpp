#include "Struct.h"

namespace grudov
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '\0';
    in >> c;
    if (in && (c != dest.del))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, Point &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Point temp_point;
    in >> temp_point.x_;
    in >> DelimiterIO{';'};
    in >> temp_point.y_;
    dest = temp_point;
    return in;
  }

  std::istream &operator>>(std::istream &in, Polygon &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::size_t count_points;
    in >> count_points;
    if (count_points < 3)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    Polygon temp_polygon;
    for (size_t i = 0; i < count_points; i++)
    {
      Point temp_point;
      in >> DelimiterIO{'('};
      in >> temp_point;
      in >> DelimiterIO{')'};
      temp_polygon.points_.push_back(temp_point);
    }
    if (in && count_points == temp_polygon.points_.size())
    {
      dest = temp_polygon;
    }
    return in;
  }

  bool Polygon::operator==(const Polygon& other) const
  {
    return (points_ == other.points_);
  }

  bool Point::operator==(const Point& other) const
  {
    return (x_ == other.x_) && (y_ == other.y_);
  }

}

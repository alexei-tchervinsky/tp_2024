#include <iostream>
#include <algorithm>
#include <iterator>
#include "Geometry.h"
#include "DataStruct.h"

namespace ermilov {
  bool Point::operator==(const Point& other)
  {
    if (x_ == other.x_ && y_ == other.y_)
    {
      return true;
    }
    else {
      return false;
    }
  }

  bool Polygon::operator==(const Polygon& other)
  {
    if (std::equal(points_.begin(), points_.end(), other.points_.begin(), other.points_.end()))
    {
      if (points_.size() != other.points_.size())
      {
        return false;
      }
      else
      {
        return true;
      }
    }
    else {
      return false;
    }
  }

  std::istream& operator>>(std::istream& in, Point& point)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }

    using sep = DelimiterIO;
    if (!(in >> sep{ '(' } >> point.x_ >> sep{ ';' } >> point.y_ >> sep{ ')' }))
    {
      in.setstate(std::ios::failbit);
    }

    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    Polygon poly;
    size_t vertexes;
    if (!(in >> vertexes) || vertexes < 3)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    using inputItr = std::istream_iterator< Point >;
    std::vector< Point > points;
    std::copy_n(inputItr{ in }, vertexes, std::back_inserter(points));
    if (in)
    {
      poly.points_ = std::move(points);
    }
    if (in && vertexes == poly.points_.size() && in.peek() == '\n')
    {
      polygon = poly;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}

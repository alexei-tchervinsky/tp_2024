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

    using itr = std::istream_iterator<Point>;
    size_t numPoints = 0;

    if (!(in >> numPoints) || numPoints < 3)
    {
      in.setstate(std::ios::failbit);
    }

    if (in)
    {
      std::copy_n(itr{ in }, numPoints, std::back_inserter(polygon.points_));
    }
    else {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}

#include "Polygon.hpp"
#include <iostream>

namespace semzin
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
    Point point;
    in >> DelimiterIO{'('};
    in >> point.x;
    in >> DelimiterIO{';'};
    in >> point.y;
    in >> DelimiterIO{')'};
    dest = point;
    return in;
  }

  std::istream &operator>>(std::istream &in, Polygon &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Polygon polygon;
    std::size_t vertexes;
    if (vertexes < 3)
    {
      in.setstate(std::ios::failbit);
    }
    Point point;
    for (std::size_t i = 0; i < vertexes; ++i)
    {
      in >> point;
      if (in)
      {
        polygon.points.push_back(point);
      }
    }

    if (vertexes != polygon.points.size() || polygon.points.size() < 3)
    {
      in.setstate(std::ios::failbit);
    }
    dest = polygon;
    return in;
  }
}

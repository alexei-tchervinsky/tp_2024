#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <vector>

namespace kladkovoj
{
  struct Point
  {
    double x;
    double y;

    Point(double x0 = 0, double y0 = 0) : x(x0), y(y0)
    {
    }

    bool operator !=( const Point& other) const
    {
      return x != other.x || y != other.y;
    }
  };

  struct Segment
  {
    Point start;
    Point end;

    bool isIntersect( const Segment& other, std::pair<double, double>* intr) const;
  };

  struct Polygon
  {
    std::vector<Point> points;

    bool operator ==(const Polygon& other) const;
    bool operator !=(const Polygon& other) const;
    bool operator <(const Polygon& other) const;

    double area( void ) const;
    std::vector<Segment> createSegmentPool(void) const;
    bool contains(const Point& pnt) const;
    bool isIntersect(const Polygon& other) const;
  };

  struct Sep
  {
    char exp;

    Sep(const char ch) : exp(ch)
    {
    }
  };

  std::istream& operator >>(std::istream& input, Sep&& res);
  std::istream& operator >>(std::istream& input, Point& res);
  std::istream& operator >>(std::istream& input, Polygon& res);
  std::ostream& operator <<(std::ostream& out, Point& pnt);
  std::ostream& operator <<(std::ostream& out, Polygon& poly);

}

#endif

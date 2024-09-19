#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <istream>

namespace ermilov
{
  struct Point {
    int x_, y_;

    bool operator==(const Point& other);
  };
  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector <Point> points_;

    bool operator==(const Polygon& other);
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);
}

#endif // !GEOMETRY_H

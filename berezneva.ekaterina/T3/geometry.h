#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include <vector>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <algorithm>

namespace berezneva
{
  struct Point
  {
    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;

    int x_, y_;
  };

  class Vector
  {
  public:
    Vector(const Point &p1, const Point &p2);
    Vector(int x_, int y_, int z);

    int getX() const { return x_; };
    int getY() const { return y_; };
    int getZ() const { return z_; };

    Vector operator*(const Vector &v) const;

  private:
    int x_, y_, z_;
  };

  class Polygon
  {
  public:
    std::vector< Point > points_;

    double getArea() const;
    bool isIntersect(const Polygon &other) const;
    bool contains(const Point &p) const;

    bool operator<(const Polygon &other) const;
    bool operator==(const Polygon &other) const;
    bool operator!=(const Polygon &other) const;
  };

  class Triangle
  {
  public:
    Triangle(const Point &a_, const Point &b_, const Point &c_);

    bool contains(const Point &p) const;
    double getArea() const;

  private:
    Point a_, b_, c_;
  };

  double getDistance(const Point &p1, const Point &p2);
}
#endif

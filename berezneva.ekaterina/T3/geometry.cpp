#include "geometry.h"

bool berezneva::Polygon::contains(const berezneva::Point &pnt) const
{
  berezneva::Point fixed = points_[0], first = points_[1];

  return std::any_of(
    points_.begin() + 2,
    points_.end(),
    [fixed, pnt, &first](berezneva::Point second)
    {
      Triangle t(fixed, first, second);
      first = second;
      return t.contains(pnt);
    }
  );
}

berezneva::Vector::Vector(const Point &p1, const Point &p2) :
  x_(p2.x_ - p1.x_), y_(p2.y_ - p1.y_), z_(0)
{
}

berezneva::Vector::Vector(int x_, int y_, int z) :
  x_(x_), y_(y_), z_(z)
{
}

berezneva::Vector berezneva::Vector::operator*(const Vector &v) const
{
  return { y_ * v.z_ - z_ * v.y_, z_ * v.x_ - x_ * v.z_, x_ * v.y_ - y_ * v.x_ };
}

bool berezneva::Triangle::contains(const Point &p) const
{
  Vector A = Vector(a_, b_) * Vector(a_, p),
    B = Vector(b_, c_) * Vector(b_, p),
    C = Vector(c_, a_) * Vector(c_, p);

  return ((A.getZ() >= 0 && B.getZ() >= 0 && C.getZ() >= 0) || (A.getZ() <= 0 && B.getZ() <= 0 && C.getZ() <= 0));
}

berezneva::Triangle::Triangle(const Point &a, const Point &b, const Point &c) :
  a_(a),
  b_(b),
  c_(c)
{
}

double berezneva::getDistance(const berezneva::Point &p1, const berezneva::Point &p2)
{
  int dx = p1.x_ - p2.x_;
  int dy = p1.y_ - p2.y_;
  return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
}

double berezneva::Triangle::getArea() const
{
  double x_ = getDistance(a_, b_);
  double y_ = getDistance(a_, c_);
  double z = getDistance(b_, c_);
  double p = (x_ + y_ + z) / 2;
  return std::sqrt(p * (p - x_) * (p - y_) * (p - z));
}

double berezneva::Polygon::getArea() const
{
  berezneva::Point fixed = points_[0], first = points_[1];

  double area = std::accumulate(
      points_.begin() + 2,
      points_.end(),
      0.0,
      [fixed, &first](double accumulator, berezneva::Point second)
      {
        accumulator += Triangle(fixed, first, second).getArea();
        first = second;
        return accumulator;
      }
  );
  return area;
}

bool berezneva::Polygon::operator<(const Polygon &other) const
{
  return getArea() < other.getArea();
}

bool berezneva::Polygon::operator==(const Polygon &other) const
{
  if (points_.size() == other.points_.size())
  {
    for (std::size_t i = 0; i < points_.size(); ++i)
    {
      if (points_[i] != other.points_[i])
        return false;
    }
    return true;
  }
  return false;
}

bool berezneva::Polygon::operator!=(const Polygon &other) const
{
  return !(*this == other);
}

bool berezneva::Point::operator==(const Point &other) const
{
  return x_ == other.x_ && y_ == other.y_;
}

bool berezneva::Point::operator!=(const Point &other) const
{
  return !(*this == other);
}

bool berezneva::Polygon::isIntersect(const Polygon &other) const
{

  return std::any_of(
    points_.begin(),
    points_.end(),
    [&other](const Point &pnt)
    {
      return other.contains(pnt);
    }
  );
}

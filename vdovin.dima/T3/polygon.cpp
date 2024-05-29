#include "polygon.hpp"
#include "delimiter.hpp"
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>


struct calculateArea
{
  vdovin::Point changP;
  double operator()(const vdovin::Point& p1, const vdovin::Point& p2);
};

double calculateArea::operator()(const vdovin::Point& p, const vdovin::Point& fixedP)
{
  double current = 0.5 * std::abs((p.x - fixedP.x) * (changP.y - fixedP.y) - (changP.x - fixedP.x) * (p.y - fixedP.y));
  changP = p;
  return current;
}

double vdovin::getAreaPol(const Polygon& pol)
{
  std::vector<double> result;
  auto functor = std::bind(calculateArea{ pol.points[1] }, std::placeholders::_1, pol.points[0]);
  std::transform(pol.points.cbegin(), pol.points.cend(), std::back_inserter(result), functor);
  return std::accumulate(result.cbegin(), result.cend(), 0.0);
}

double vdovin::getArea(const std::vector<Polygon>& pols)
{
  std::vector<double> result;
  std::transform(pols.cbegin(), pols.cend(), std::back_inserter(result), getAreaPol); 
  return std::accumulate(result.cbegin(), result.cend(), 0.0);
}

std::istream& vdovin::operator>>(std::istream& in, Polygon& pol)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t countAngles = 0;
  in >> countAngles;
  const size_t minAngles = 3;
  if (countAngles < minAngles)
  { 
    in.setstate(std::ios::failbit);
    return in;
  }
  using input_it_t = std::istream_iterator<Point>;
  std::vector<Point> temp(countAngles, Point{0, 0});
  std::copy_n(input_it_t{in}, countAngles, temp.begin());
  if (countAngles == temp.size())
  {
    pol.points = temp;
  }
  else
  {
    in.setstate(std::ios::failbit);
  } 
  return in;
}

std::istream& vdovin::operator>>(std::istream& in, Point& p)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point point;
  in >> Delimiter{'('};
  in >> point.x;
  in >> Delimiter{';'}; 
  in >> point.y;
  in >> Delimiter{')'};
  p = point;
  return in;
}

bool vdovin::operator<(const Point& lhs, const Point& rhs)
{
  return (lhs.x < rhs.x) && (lhs.y < rhs.y);
}
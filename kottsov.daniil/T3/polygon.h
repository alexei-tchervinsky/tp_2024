#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <numeric>

#ifndef POLYGON
#define POLYGON
// RMECHO SAME
namespace poly
{
  class iofmtguard
  {
    public:
      iofmtguard(std::basic_ios<char>& s);
      ~iofmtguard();
    private:
      std::basic_ios<char>& s_;
      char fill_;
      std::streamsize precision_;
      std::basic_ios<char>::fmtflags fmt_;
  };
  struct Point
  {
    Point();
    Point(int x, int y);
    int x_;
    int y_;
  };
  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, const Point& point);
  bool operator==(const Point& first, const Point& second);
  struct Polygon
  {
    std::vector<Point> polygon_;
  };
  std::istream& operator>>(std::istream& in, Polygon& polyg);
  std::ostream& operator<<(std::ostream& out, const Polygon& polyg);
  bool operator==(const Polygon& first, const Polygon& second);
  double getPolyArea(const Polygon& polygon);
  struct DefInput
  {
    char exp;
  };
  std::istream& operator>>(std::istream& in, DefInput&& def);
  struct NumberInput
  {
    size_t& ref;
  };
  std::istream& operator>>(std::istream& in, NumberInput&& num);
};
#endif

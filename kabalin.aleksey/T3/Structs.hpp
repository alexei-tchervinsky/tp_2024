#ifndef STRUCTS_H
#define STRUCTS_H
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

namespace kabalin {
struct Point {
  int x, y;
  bool operator!=(Point &otherPoint);
  bool operator<(const Point &other) const {
    if (x != other.x)
      return x < other.x;
    return y < other.y;
  }
};
struct Polygon {
  std::vector<Point> points;
  double area(void) const;
  bool operator==(Polygon &otherData);
  bool isSame(const Polygon &other) const;
};
struct Delimetr {
  char del;
  Delimetr(const char el) : del(el){};
};

std::istream &operator>>(std::istream &input, Delimetr &&del);
std::istream &operator>>(std::istream &input, Point &point);
std::istream &operator>>(std::istream &input, Polygon &data);
std::ostream &operator<<(std::ostream &output, const Point &point);
std::ostream &operator<<(std::ostream &output, const Polygon &data);
}; // namespace kabalin
#endif

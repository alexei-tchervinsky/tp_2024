#ifndef HEAD_HPP
#define HEAD_HPP

#include <vector>
#include <iostream>
#include <memory>
#include <cmath>

struct Point {
    int x, y;
};

struct Polygon {
    std::vector<Point> points;

    bool operator==(const Polygon& other) const {
        return points == other.points;
    }
};

double calculateArea(const Polygon& polygon);

std::ostream& operator<<(std::ostream& os, const Polygon& polygon);

#endif // HEAD_HPP

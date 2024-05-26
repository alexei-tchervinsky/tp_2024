#ifndef STRUCT_MUNGOI_H
#define STRUCT_MUNGOI_H

#include <iostream>
#include <vector>

namespace mungoisheller
{
    struct DelimiterIO
    {
        char del;
    };

    struct Point
    {
        int x, y;
        bool operator==(const Point& other) const
        {
            return (this->x == other.x) && (this->y == other.y);
        }
    };

    struct Polygon
    {
        std::vector<Point> points;
        bool operator==(const Polygon& other) const
        {
            return (this->points == other.points);
        }
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, Point& dest);
    std::istream& operator>>(std::istream& in, Polygon& dest);
    double area(const Polygon& polygon);
}

#endif

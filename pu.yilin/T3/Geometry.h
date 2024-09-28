#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

namespace Geometry {
    struct DelimiterIO {
        char del;
    };

    struct Point {
        int x, y;

        bool operator==(const Point &other) const {
            return (this->x == other.x) && (this->y == other.y);
        }
    };

    struct Polygon {
        std::vector<Point> points;

        bool operator==(const Polygon &other) const {
            return (this->points == other.points);
        }
    };

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest);

    std::istream &operator>>(std::istream &in, Point &dest);

    std::istream &operator>>(std::istream &in, Polygon &dest);

    double computeArea(const Polygon &polygon);

    void areaParam(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out);

    void maxParam(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out);

    void minParam(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out);

    void countParam(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out);

    void lessAreaParam(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out);

    void intersectionsParam(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out);
}

#endif

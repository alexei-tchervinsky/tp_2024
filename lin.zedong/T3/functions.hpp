#ifndef STRUCT_HPP
#define STRUCT_HPP
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

namespace geometry
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
        std::vector< Point > points;
        bool operator==(const Polygon& other) const
        {
          return (this->points == other.points);
        }
    };

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
    std::istream &operator>>(std::istream &in, Point &dest);
    std::istream &operator>>(std::istream &in, Polygon &dest);
    std::size_t get_count(std::size_t param, const std::vector< geometry::Polygon > polygons);
    std::size_t get_seq(std::vector< geometry::Polygon >::const_iterator begin,
    std::vector< geometry::Polygon >::const_iterator end, const Polygon& param);

    double area(const Polygon& polygon);
    double get_sum(double result, const Polygon& polygon, std::size_t param);
    double get_area(std::size_t param, const std::vector< geometry::Polygon > polygons);
    double get_max(std::size_t param, const std::vector< geometry::Polygon > polygons);
    double get_min(std::size_t param, const std::vector< geometry::Polygon > polygons);

    bool get_rects(const Point& start, const Point& end1, const Point& end2, const Point& end3);

    void area_param(const std::vector< geometry::Polygon > polygons, std::istream &in, std::ostream &out);
    void max_param(const std::vector< geometry::Polygon > polygons, std::istream &in, std::ostream &out);
    void min_param(const std::vector< geometry::Polygon > polygons, std::istream &in, std::ostream &out);
    void count_param(const std::vector< geometry::Polygon > polygons, std::istream &in, std::ostream &out);
    void rects_param(const std::vector< geometry::Polygon > polygons, std::istream &in, std::ostream &out);
    void maxseq_param(const std::vector< geometry::Polygon > polygons, std::istream &in, std::ostream &out);
}

#endif

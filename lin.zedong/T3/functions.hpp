#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cmath>
#include <string>
#include <numeric>

namespace geometry
{
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
        double calculate_area() const;
        bool operator==(const Polygon& other) const
        {
            return this->points == other.points;
        }
    };

    std::istream& operator>>(std::istream& in, Point& dest);
    std::istream& operator>>(std::istream& in, Polygon& dest);

    void read_polygons(std::istream& in, std::vector<Polygon>& polygons);

    bool is_rectangle(const Polygon& poly);

    double get_area_sum(const std::vector<Polygon>& polygons, std::function<bool(const Polygon&)> pred);
    double get_mean_area(const std::vector<Polygon>& polygons);
    double get_extreme_area(const std::vector<Polygon>& polygons, bool find_max);

    int get_count(const std::vector<Polygon>& polygons, std::function<bool(const Polygon&)> pred);
    int get_extreme_vertex_count(const std::vector<Polygon>& polygons, bool find_max);
    int count_rectangles(const std::vector<Polygon>& polygons);
    int max_sequence(const std::vector<Polygon>& polygons, const Polygon& target);

    void area_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void count_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void rects_param(const std::vector<Polygon>& polygons, std::istream&, std::ostream& out);
    void maxseq_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void extreme_param(const std::vector<Polygon>& polygons, std::istream&, std::ostream& out, bool find_max, const std::string& type);
}

#endif

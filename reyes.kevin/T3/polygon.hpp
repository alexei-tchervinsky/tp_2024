#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <fstream>
#include <algorithm>
#include <iostream>
#include "struct.hpp"
#include <limits>
#include <iomanip>
#include <exception>
#include <iterator>

namespace nspace
{
    double get_sum(double result, const Polygon& polygon, std::size_t param);
    double get_area(std::size_t param, const std::vector<Polygon>& polygons);
    double get_max(std::size_t param, const std::vector<Polygon>& polygons);
    double get_min(std::size_t param, const std::vector<Polygon>& polygons);
    std::size_t get_count(std::size_t param, const std::vector<Polygon>& polygons);
    bool get_rects(const Point& start, const Point& end1, const Point& end2, const Point& end3);
    std::size_t get_seq(std::vector<Polygon>::const_iterator begin,
        std::vector<Polygon>::const_iterator end, const Polygon& param);
    bool intersects(const Polygon& a, const Polygon& b);

    void area_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void max_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void min_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void count_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void rects_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void intersections_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
}

#endif

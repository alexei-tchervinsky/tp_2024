#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <iostream>
#include <functional>
#include <map>
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
        friend std::istream& operator>>(std::istream& is, Polygon& poly);
        bool operator==(const Polygon& other) const;
    };

    class Shape
    {
        public:
        Shape(std::vector<Point> vertices);

        int countVertices() const;
        int countOddVertices() const;
        int countEvenVertices() const;
        double area() const;
        void printShapeData() const;
        const std::vector<Point>& getVertices() const;

        private:
        std::vector<Point> vertices_;
    };

    std::istream& operator>>(std::istream& in, Point& dest);
    std::string generate_polygon_description(const Polygon& polygon);

    void read_polygons(std::istream& in, std::vector<Polygon>& polygons);

    bool is_rectangle(const Polygon& poly);

    double get_area_sum(const std::vector<Polygon>& polygons, std::function<bool(const Polygon&)> pred);
    double get_mean_area(const std::vector<Polygon>& polygons);

    int get_count(const std::vector<Polygon>& polygons, std::function<bool(const Polygon&)> pred);
    int count_rectangles(const std::vector<Polygon>& polygons);
    int max_sequence(const std::vector<Polygon>& polygons, const Polygon& target);

    void area_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void count_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
    void rects_param(const std::vector<Polygon>& polygons, std::istream&, std::ostream& out);
    void maxseq_param(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);

    int count_even_vertexes(const std::vector<Polygon>& polygons);
    int count_odd_vertexes(const std::vector<Polygon>& polygons);
    int count_specific_vertexes(const std::vector<Polygon>& polygons, int num);
    int max_sequence_of_polygon(const std::vector<Polygon>& polygons, const std::string& polygonDesc);

    void countCommand(const std::vector<Shape>& shapes, const std::string& type);
    void areaCommand(const std::vector<Shape>& shapes, const std::string& type);
    void maxCommand(const std::vector<Shape>& shapes, const std::string& type);
    void rectsCommand(const std::vector<Shape>& shapes);
}

#endif

#include "head.hpp"

double calculateArea(const Polygon & polygon) {
    double area = 0.0;
    size_t n = polygon.points.size();
    for (size_t i = 0; i < n; ++i) {
        const Point& a = polygon.points[i];
        const Point& b = polygon.points[(i + 1) % n];
        area += a.x * b.y - b.x * a.y;
    }
    return std::fabs(area) / 2.0;
}

std::ostream& operator<<(std::ostream& os, const Polygon& polygon) {
    os << polygon.points.size();
    for (const auto& point : polygon.points) {
        os << " (" << point.x << ";" << point.y << ")";
    }
    return os;
}
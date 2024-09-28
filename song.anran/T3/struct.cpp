#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>

struct Point {
    int x, y;
};

struct Polygon {
    std::vector<Point> points;
    int vertexCount() const {
        return points.size();
    }
};

double calculateArea(const Polygon& polygon) {
    double area = 0.0;
    int j = polygon.vertexCount() - 1;
    for (int i = 0; i < polygon.vertexCount(); i++) {
        area += (polygon.points[j].x + polygon.points[i].x) * (polygon.points[j].y - polygon.points[i].y);
        j = i;
    }
    return std::abs(area / 2.0);
}

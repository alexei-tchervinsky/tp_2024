#include "Geometry.h"
#include <numeric>
#include <functional>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <exception>
#include <iterator>

namespace Geometry {
    std::istream &operator>>(std::istream &in, DelimiterIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        char c = '\0';
        in >> c;
        if (in && (c != dest.del)) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, Point &dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        Point tempPoint{};
        in >> tempPoint.x;
        in >> DelimiterIO{';'};
        in >> tempPoint.y;
        dest = tempPoint;
        return in;
    }

    std::istream &operator>>(std::istream &in, Polygon &dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        std::size_t countPoints;
        in >> countPoints;
        if (countPoints < 3) {
            in.setstate(std::ios::failbit);
            return in;
        }
        Polygon tempPolygon;
        for (size_t i = 0; i < countPoints; i++) {
            Point tempPoint{};
            in >> DelimiterIO{'('};
            in >> tempPoint;
            in >> DelimiterIO{')'};
            tempPolygon.points.push_back(tempPoint);
        }
        if (in && countPoints == tempPolygon.points.size()) {
            dest = tempPolygon;
        }
        return in;
    }

    double computeArea(const Polygon &polygon) {
        double area = 0.0;
        std::size_t countPoints = polygon.points.size();
        for (std::size_t i = 0; i < countPoints; i++) {
            const Point &p1 = polygon.points[i];
            const Point &p2 = polygon.points[(i + 1) % countPoints];
            area += (p1.x * p2.y - p1.y * p2.x);
        }
        return 0.5 * std::abs(area);
    }

    double getSumArea(double result, const Polygon &polygon, std::size_t param) {
        if (param == 0 ||
            (param == 1 && polygon.points.size() % 2 != 0) ||
            (param == 2 && polygon.points.size() % 2 == 0) ||
            param == polygon.points.size()) {
            return result + computeArea(polygon);
        }
        return result;
    }

    double getArea(std::size_t param, const std::vector<Polygon> &polygons) {
        std::function<double(double, const Polygon &)> binaryOperation = [param](auto &&PH1, auto &&PH2) {
            return getSumArea(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2), param);
        };
        double sum = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, binaryOperation);
        if (param == 0 && !polygons.empty()) {
            return sum / static_cast<double>(polygons.size());
        }
        return sum;
    }

    double getMax(std::size_t param, const std::vector<Polygon> &polygons) {
        if (polygons.empty()) {
            throw std::invalid_argument("No polygons available");
        }
        if (param == 0) {
            return computeArea(
                    *std::max_element(polygons.cbegin(), polygons.cend(), [](const Polygon &a, const Polygon &b) {
                        return computeArea(a) < computeArea(b);
                    })
            );
        }
        return static_cast<double>(std::max_element(polygons.cbegin(), polygons.cend(),
                                                    [](const Polygon &a, const Polygon &b) {
                                                        return a.points.size() < b.points.size();
                                                    })->points.size());
    }

    double getMin(std::size_t param, const std::vector<Polygon> &polygons) {
        if (polygons.empty()) {
            throw std::invalid_argument("No polygons available");
        }
        if (param == 0) {
            return computeArea(
                    *std::min_element(polygons.cbegin(), polygons.cend(), [](const Polygon &a, const Polygon &b) {
                        return computeArea(a) < computeArea(b);
                    })
            );
        }
        return static_cast<double>(std::min_element(polygons.cbegin(), polygons.cend(),
                                                    [](const Polygon &a, const Polygon &b) {
                                                        return a.points.size() < b.points.size();
                                                    })->points.size());
    }

    std::size_t getCount(std::size_t param, const std::vector<Polygon> &polygons) {
        if (param == 1) {
            return std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon &a) {
                return a.points.size() % 2 != 0;
            });
        } else if (param == 2) {
            return std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon &a) {
                return a.points.size() % 2 == 0;
            });
        } else {
            return std::count_if(polygons.cbegin(), polygons.cend(), [param](const Polygon &a) {
                return a.points.size() == param;
            });
        }
    }

    int orientation(const Point &p, const Point &q, const Point &r) {
        int val = (q.y - p.y) * (r.x - q.x) -
                  (q.x - p.x) * (r.y - q.y);
        if (val == 0) return 0;
        return (val > 0) ? 1 : 2;
    }

    bool onSegment(const Point &p, const Point &q, const Point &r) {
        if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
            return true;
        return false;
    }

    bool doLinesIntersect(const Point &p1, const Point &q1, const Point &p2, const Point &q2) {
        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        if (o1 != o2 && o3 != o4)
            return true;

        if (o1 == 0 && onSegment(p1, p2, q1)) return true;
        if (o2 == 0 && onSegment(p1, q2, q1)) return true;
        if (o3 == 0 && onSegment(p2, p1, q2)) return true;
        if (o4 == 0 && onSegment(p2, q1, q2)) return true;

        return false;
    }

    bool isPointInPolygon(const Point &point, const Polygon &polygon) {
        std::size_t n = polygon.points.size();
        if (n < 3) return false;
        Point extreme = {std::numeric_limits<int>::max(), point.y};
        int count = 0;
        std::size_t i = 0;
        do {
            std::size_t next = (i + 1) % n;
            if (doLinesIntersect(polygon.points[i], polygon.points[next], point, extreme)) {
                if (orientation(polygon.points[i], point, polygon.points[next]) == 0)
                    return onSegment(polygon.points[i], point, polygon.points[next]);
                count++;
            }
            i = next;
        } while (i != 0);
        return count % 2 == 1;
    }

    bool polygonsIntersect(const Polygon &poly1, const Polygon &poly2) {
        for (size_t i = 0; i < poly1.points.size(); i++) {
            Point p1 = poly1.points[i];
            Point q1 = poly1.points[(i + 1) % poly1.points.size()];
            for (size_t j = 0; j < poly2.points.size(); j++) {
                Point p2 = poly2.points[j];
                Point q2 = poly2.points[(j + 1) % poly2.points.size()];
                if (doLinesIntersect(p1, q1, p2, q2)) {
                    return true;
                }
            }
        }
        if (isPointInPolygon(poly1.points[0], poly2))
            return true;
        if (isPointInPolygon(poly2.points[0], poly1))
            return true;
        return false;
    }

    void areaParam(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out) {
        std::string param;
        in >> param;
        try {
            if (param == "MEAN" && !polygons.empty()) {
                out << std::setprecision(1) << std::fixed << getArea(0, polygons) << '\n';
            } else if (param == "ODD") {
                out << std::setprecision(1) << std::fixed << getArea(1, polygons) << '\n';
            } else if (param == "EVEN") {
                out << std::setprecision(1) << std::fixed << getArea(2, polygons) << '\n';
            } else if (std::stoll(param) >= 3) {
                out << std::setprecision(1) << std::fixed << getArea(std::stoll(param), polygons) << '\n';
            } else {
                throw std::invalid_argument("<INVALID COMMAND>");
            }
        }
        catch (std::exception &) {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
    }

    void maxParam(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out) {
        std::string param;
        in >> param;
        if (param == "AREA") {
            out << std::setprecision(1) << std::fixed << getMax(0, polygons) << '\n';
        } else if (param == "VERTEXES") {
            out << std::setprecision(0) << std::fixed << getMax(1, polygons) << '\n';
        } else {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
    }

    void minParam(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out) {
        std::string param;
        in >> param;
        if (param == "AREA") {
            out << std::setprecision(1) << std::fixed << getMin(0, polygons) << '\n';
        } else if (param == "VERTEXES") {
            out << std::setprecision(0) << std::fixed << getMin(1, polygons) << '\n';
        } else {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
    }

    void countParam(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out) {
        std::string param;
        in >> param;
        try {
            if (param == "ODD") {
                out << std::setprecision(0) << std::fixed << getCount(1, polygons) << '\n';
            } else if (param == "EVEN") {
                out << std::setprecision(0) << std::fixed << getCount(2, polygons) << '\n';
            } else if (std::stoll(param) >= 3) {
                out << std::setprecision(0) << std::fixed << getCount(std::stoll(param), polygons) << '\n';
            } else {
                throw std::invalid_argument("<INVALID COMMAND>");
            }
        }
        catch (std::exception &) {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
    }

    void lessAreaParam(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out) {
        Polygon paramPolygon;
        in >> paramPolygon;
        if (!in || in.peek() != '\n') {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
        double areaParamPolygon = computeArea(paramPolygon);
        size_t count = std::count_if(polygons.begin(), polygons.end(), [areaParamPolygon](const Polygon &p) {
            return computeArea(p) < areaParamPolygon;
        });
        out << count << '\n';
    }

    void intersectionsParam(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out) {
        Polygon paramPolygon;
        in >> paramPolygon;
        if (!in || in.peek() != '\n') {
            throw std::invalid_argument("<INVALID COMMAND>");
        }
        size_t count = std::count_if(polygons.begin(), polygons.end(), [&paramPolygon](const Polygon &p) {
            return polygonsIntersect(p, paramPolygon);
        });
        out << count << '\n';
    }
}

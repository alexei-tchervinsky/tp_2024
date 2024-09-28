#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Polygon.hpp"
#include <string>
#include <functional>

namespace AliKn
{
	void Area(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
	void OddArea(const std::vector<Polygon>& polygons, std::ostream& out);
	void EvenArea(const std::vector<Polygon>& polygons, std::ostream& out);
	void AreaVersNum(std::size_t vertexes, const std::vector<Polygon>& polygons, std::ostream& out);
	void MeanArea(const std::vector<Polygon>& polygons, std::ostream& out);
	double getArea(const Polygon& polygon);
	double sumAreas(const std::vector<Polygon>& polygons);

	void maxArea(const std::vector<Polygon>& polygons, std::ostream& out);
	void Max(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
	void maxVertexes(const std::vector<Polygon>& polygons, std::ostream& out);

	void Min(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
	void AreaMin(const std::vector<Polygon>& polygons, std::ostream& out);
	void MinVertexes(const std::vector<Polygon>& polygons, std::ostream& out);

	void Count(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
	void CountOdd(const std::vector<Polygon>& polygons, std::ostream& out);
	void CountEven(const std::vector<Polygon>& polygons, std::ostream& out);
	void CountVertexes(std::size_t vertexes, const std::vector<Polygon>& polygons, std::ostream& out);

	void Perms(const std::vector<Polygon>& polygons, std::ostream& out, std::istream& in);
	bool checkPerms(const Polygon& left, const Polygon& right);
	bool checkPoints(const Polygon& polygon, const Point& point);

	void Rightshapes(const std::vector<Polygon>& polygons, std::ostream& out);
	bool isRightAngle(const Polygon& polygon);
	Point vectorOnCoords(const Point& firstPoint, const Point& secondPoint);
	double cosFromVects(const Point& firstPoint, const Point& secondPoint);

	void displayMessage(std::ostream& out, const std::string& message);
}
#endif
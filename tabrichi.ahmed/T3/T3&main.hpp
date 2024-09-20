#ifndef T3&MAIN_HPP
#define T3&MAIN_HPP

#include "head.hpp"
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <functional>

void readPolygonsFromFile(const std::string& filename, std::vector<std::shared_ptr<Polygon>>& polygons);
double calculateArea(const std::shared_ptr<Polygon>& polygon);
double triangleArea(const Point& a, const Point& b, const Point& c);
void processCommand(const std::string& command, const std::vector<std::shared_ptr<Polygon>>& polygons);
void commandArea(const std::string& args, const std::vector<std::shared_ptr<Polygon>>& polygons);
void commandMax(const std::string& args, const std::vector<std::shared_ptr<Polygon>>& polygons);
void commandMin(const std::string& args, const std::vector<std::shared_ptr<Polygon>>& polygons);
void commandCount(const std::string& args, const std::vector<std::shared_ptr<Polygon>>& polygons);
void commandLessArea(const std::string& args, const std::vector<std::shared_ptr<Polygon>>& polygons);
void commandSame(const std::string& args, const std::vector<std::shared_ptr<Polygon>>& polygons);

#endif // T3&MAIN_HPP

#include <algorithm>
#include <map>
#include <functional>
#include <string>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <exception>
#include <vector>
#include "Functions.h"

using namespace std::placeholders;

namespace ermilov
{
  std::ostream& chooseCommand(std::istream& in, std::ostream& out, std::vector<Polygon>& polygons)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return out;
    }

    std::string commandType, option;
    in >> commandType >> option;

    if (commandType == "AREA")
    {
      std::map< std::string, std::function< double(const std::vector< Polygon >& data) > > commands;
      {
        commands["EVEN"] = areaEven;
        commands["ODD"] = areaOdd;
        commands["MEAN"] = areaMean;
      }

      out << std::fixed << std::setprecision(1);
      try
      {
        out << commands.at(option)(polygons) << "\n";
      }
      catch (const std::out_of_range& e)
      {
        if (std::isdigit(option[0]) && std::stoi(option) > 2)
        {
          out << areaNum(std::stoi(option), polygons) << "\n";
        }
        else
        {
          throw std::logic_error("BAD COMMAND TYPE");
        }
      }
    }
    else if (commandType == "MAX")
    {
      std::map< std::string, std::function< double(const std::vector< Polygon >& data) > > commands;
      {
        commands["AREA"] = maxArea;
        commands["VERTEXES"] = maxVert;
      }

      if (option == "AREA")
      {
        out << std::fixed << std::setprecision(1);
      }

      try
      {
        out << commands.at(option)(polygons) << "\n";
      }
      catch (const std::out_of_range& e)
      {
        throw std::logic_error("BAD COMMAND TYPE");
      }
    }
    else if (commandType == "MIN")
    {
      std::map< std::string, std::function< double(const std::vector< Polygon >& data) > > commands;
      {
        commands["AREA"] = minArea;
        commands["VERTEXES"] = minVert;
      }

      if (option == "AREA")
      {
        out << std::fixed << std::setprecision(1);
      }
      
      try
      {
        out << commands.at(option)(polygons) << "\n";
      }
      catch (const std::out_of_range& e)
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
    }
    else if (commandType == "COUNT")
    {
      std::map< std::string, std::function< double(std::vector< Polygon >& data) > > commands;
      {
        commands["EVEN"] = countEven;
        commands["ODD"] = countOdd;
      }
      try
      {
        out << commands.at(option)(polygons) << "\n";
      }
      catch (const std::out_of_range& e)
      {
        if (std::isdigit(option[0]) && std::stoi(option) > 2)
        {
          out << countNum(std::stoi(option), polygons) << "\n";
        }
        else
        {
          throw std::logic_error("<INVALID COMMAND>");
        }
      }
    }
    else if (commandType == "RMECHO")
    {
      out << rmecho(polygons, in);
    }
    else if (commandType == "INTERSECTIONS")
    {
      if (polygons.empty())
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      out << intersections(polygons, in);
      }
    else
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    return out;
  }

  double areaEven(const std::vector<Polygon>& polygons)
  {
    double sumArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, sumEven);
    return sumArea;
  }

  double areaOdd(const std::vector<Polygon>& polygons)
  {
    double sumArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, sumOdd);
    return sumArea;
  }

  double areaMean(const std::vector<Polygon>& polygons)
  {
    if (polygons.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    double sumArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, sumAll) / polygons.size();
    return sumArea;
  }

  double areaNum(int vertNum, const std::vector<Polygon>& polygons)
  {
    double sumArea = std::accumulate(polygons.begin(), polygons.end(), 0, std::bind(sumNum, _1, _2, vertNum));
    return sumArea;
  }

  double maxArea(const std::vector<Polygon>& polygons)
  {
    std::vector<double> areaList(polygons.size());

    std::transform(polygons.begin(), polygons.end(), std::back_inserter(areaList), getArea);
    std::sort(areaList.begin(), areaList.end());

    return areaList[areaList.size() - 1];
  }

  double maxVert(const std::vector<Polygon>& polygons)
  {
    std::vector< int > vertexList;
    std::transform(polygons.begin(), polygons.end(),
      std::back_inserter(vertexList),
      [](const Polygon& temp) { return temp.points_.size(); }
    );
    std::sort(vertexList.begin(), vertexList.end());
    return vertexList[vertexList.size() - 1];
  }

  double minArea(const std::vector<Polygon>& polygons)
  {
    std::vector<double> areaList(polygons.size());

    std::transform(polygons.begin(), polygons.end(), std::back_inserter(areaList), getArea);
    std::sort(areaList.begin(), areaList.end());

    return areaList[0];
  }

  double minVert(const std::vector<Polygon>& polygons)
  {
    std::vector< int > vertexList;
    std::transform(polygons.begin(), polygons.end(),
      std::back_inserter(vertexList),
      [](const Polygon& temp) { return temp.points_.size(); }
    );
    std::sort(vertexList.begin(), vertexList.end());
    return vertexList[0];
  }

  int countEven(const std::vector<Polygon>& polygons)
  {
    if (polygons.empty())
    {
      return 0;
    }

    int amount = std::count_if(
      polygons.begin(), polygons.end(),
      [](const Polygon& temp) { return temp.points_.size() % 2 == 0; }
    );
    return amount;
  }

  int countOdd(const std::vector<Polygon>& polygons)
  {
    if (polygons.empty())
    {
      return 0;
    }

    int amount = std::count_if(
      polygons.begin(), polygons.end(),
      [](const Polygon& temp) { return temp.points_.size() % 2 != 0; }
    );
    return amount;
  }

  int countNum(size_t vertNum, const std::vector<Polygon>& polygons)
  {
    if (polygons.empty())
    {
      return 0;
    }

    int amount = std::count_if(
      polygons.begin(), polygons.end(),
      [vertNum](const Polygon& temp) { return temp.points_.size() == vertNum; }
    );
    return amount;
  }

  int rmecho(std::vector<Polygon>& polygons, std::istream& in)
  {
    size_t oldSize = polygons.size();
    if (polygons.size() == 0)
    {
      return 0;
    }

    Polygon deletePolygon;

    std::istream::sentry guard(in);
    if (!guard)
    {
      return 0;
    }

    if (!(in >> deletePolygon))
    {
      throw std::logic_error("BAD POLYGON");
    }

    bool found = false;
    auto pos = std::remove_if(
      polygons.begin(), polygons.end(),
      [&deletePolygon, &found](Polygon& temp)
      {
        if (temp == deletePolygon && found)
        {
          return true;
        }
        else if (temp == deletePolygon)
        {
          found = true;
        }
        return false;
      }
    );

    polygons.erase(pos, polygons.end());
    size_t removedAmount = oldSize - polygons.size();
    return removedAmount;
  }

  int intersections(const std::vector<Polygon>& polygons, std::istream& in)
  {
    if (polygons.size() == 0) {
      return 0;
    }

    Polygon intersectPolygon;

    std::istream::sentry guard(in);
    if (!guard)
    {
      return 0;
    }

    if (!(in >> intersectPolygon))
    {
      throw std::logic_error("BAD POLYGON");
    }

    int amount = std::count_if(polygons.begin(), polygons.end(),
      std::bind(areIntersect, _1, intersectPolygon)
    );

    return amount;
  }


  //functions
  double getArea(const Polygon& polygon)
  {
    std::vector<int> values(polygon.points_.size());

    std::transform(++polygon.points_.cbegin(), polygon.points_.cend(),
      polygon.points_.cbegin(), values.begin(), getSubArea);

    values.push_back(getSubArea(polygon.points_.front(), polygon.points_.back()));
    int area = std::accumulate(values.cbegin(), values.cend(), 0);
    return abs(area) / 2.0;
  }

  int getVertAmount(const Polygon& polygon)
  {
    return polygon.points_.size();
  }

  int getSubArea(const Point& first, const Point& second)
  {
    int value = (first.x_ * second.y_) - (first.y_ * second.x_);
    return value;
  }

  double sumEven(double result, const Polygon& polygon)
  {
    if (polygon.points_.size() % 2 == 0)
    {
      return result + getArea(polygon);
    }
    else
    {
      return result;
    }
  }

  double sumOdd(double result, const Polygon& polygon)
  {
    if (polygon.points_.size() % 2 != 0)
    {
      return result + getArea(polygon);
    }
    else
    {
      return result;
    }
  }

  double sumNum(double result, const Polygon& polygon, size_t vertNum)
  {
    if (polygon.points_.size() == vertNum)
    {
      return result + getArea(polygon);
    }
    else
    {
      return result;
    }
  }

  double sumAll(double result, const Polygon& polygon)
  {
    return result + getArea(polygon);
  }

  bool areIntersect(const Polygon& first, const Polygon& second)
  {
    Point firstMax = getMaxPoint(first);
    Point firstMin = getMinPoint(first);
    Point secondMax = getMaxPoint(second);
    Point secondMin = getMinPoint(second);

    bool intersection = ((firstMax.x_ >= secondMin.x_) &&
      (firstMax.y_ >= secondMin.y_) &&
      (firstMin.x_ <= secondMax.x_) &&
      (firstMin.y_ <= secondMax.y_));
    return intersection;
  }

  Point getMaxPoint(const Polygon& polygon) {
    Point result;
    result.x_ = (*std::max_element(polygon.points_.begin(), polygon.points_.end(), isBiggerX)).x_;
    result.y_ = (*std::max_element(polygon.points_.begin(), polygon.points_.end(), isBiggerY)).y_;
    return result;
  }

  Point getMinPoint(const Polygon& polygon) {
    Point result;
    result.x_ = (*std::min_element(polygon.points_.begin(), polygon.points_.end(), isSmallerX)).x_;
    result.y_ = (*std::min_element(polygon.points_.begin(), polygon.points_.end(), isSmallerY)).y_;
    return result;
  }

  bool isBiggerX(const Point& first, const Point& second)
  {
    return (first.x_ < second.x_);
  }

  bool isBiggerY(const Point& first, const Point& second)
  {
    return (first.y_ < second.y_);
  }

  bool isSmallerX(const Point& first, const Point& second)
  {
    return (first.x_ < second.x_);
  }

  bool isSmallerY(const Point& first, const Point& second)
  {
    return (first.y_ < second.y_);
  }
}

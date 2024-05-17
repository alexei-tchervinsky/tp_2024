#include "operations.h"

std::istream& poly::operator>>(std::istream& in, ExpressionIO&& exp)
{
  std::istream::sentry ward(in);
  if (!ward)
  {
    throw std::logic_error("istream failure");
    return in;
  }
  in >> exp.ref;
  if (!in)
  {
    throw std::logic_error("invalid exp");
    return in;
  }
  return in;
}
void poly::ioUI(std::vector<Polygon>& vector, std::istream& in, std::ostream& out)
{
  std::istream::sentry ward(in);
  if (!ward)
  {
    throw std::logic_error("istream failure");
    return;
  }
  std::ostream::sentry warden(out);
  if (!warden)
  {
    throw std::logic_error("ostream failure");
    return;
  }
  iofmtguard fmtguard(out);
  std::string operation;
  {
    using string = ExpressionIO;
    using symbol = DefInput;
    using number = NumberInput;
    in >> string{ operation };
    if (!in)
    {
      in.setstate(std::ios::failbit);
      throw std::logic_error("invalid cmd");
      return;
    }
    if (operation == "AREA")
    {
      std::string sub;
      in >> string{ sub };
      if (!in)
      {
        in.setstate(std::ios::failbit);
        throw std::logic_error("invalid cmd");
        return;
      }
      if (sub == "ODD")
      {
        out << std::setprecision(1) << std::fixed << getTotalArea(vector,1) << '\n';
        return;
      }
      else if (sub == "EVEN")
      {
        out << std::setprecision(1) << std::fixed << getTotalArea(vector,0) << '\n';
        return;
      }
      else if (sub == "MEAN")
      {
        out << std::setprecision(1) << std::fixed << getMeanArea(vector) << '\n';
        return;
      }
      else
      {
        try
        {
          int num{ std::stoi(sub) };
          out << std::setprecision(1) << std::fixed << getSpecArea(vector,num) << '\n';
        }
        catch (const std::invalid_argument& ex)
        {
          throw std::logic_error("invalid cmd");
          return;
        }
      }
    }
    else if (operation == "MAX")
    {
      std::string sub;
      in >> string{ sub };
      if (!in)
      {
        in.setstate(std::ios::failbit);
        throw std::logic_error("invalid cmd");
        return;
      }
      if (sub == "AREA")
      {
        out << std::setprecision(1) << std::fixed << getMaxArea(vector) << '\n';
        return;
      }
      else if (sub == "VERTEXES")
      {
        out << getMaxVert(vector) << '\n';
        return;
      }
      else
      {
        throw std::logic_error("invalid cmd");
        return;
      }
    }
    else if (operation == "MIN")
    {
      std::string sub;
      in >> string{ sub };
      if (!in)
      {
        in.setstate(std::ios::failbit);
        throw std::logic_error("invalid cmd");
        return;
      }
      if (sub == "AREA")
      {
        out << std::setprecision(1) << std::fixed << getMinArea(vector) << '\n';
        return;
      }
      else if (sub == "VERTEXES")
      {
        out << getMinVert(vector) << '\n';
        return;
      }
      else
      {
        throw std::logic_error("invalid cmd");
        return;
      }
    }
    else if (operation == "COUNT")
    {
      std::string sub;
      in >> string{ sub };
      if (!in)
      {
        in.setstate(std::ios::failbit);
        throw std::logic_error("invalid cmd");
        return;
      }
      if (sub == "EVEN")
      {
        out << countTotal(vector,0) << '\n';
        return;
      }
      else if (sub == "ODD")
      {
        out << countTotal(vector,1) << '\n';
        return;
      }
      else
      {
        try
        {
          int num{ std::stoi(sub) };
          out << countSpec(vector, num) << '\n';
        }
        catch(const std::invalid_argument& ex)
        {
          throw std::logic_error("invalid cmd");
          return;
        }
      }
    }
    else if (operation == "RMECHO")
    {
      Polygon polygon;
      in >> polygon;
      if (!in)
      {
        in.setstate(std::ios::failbit);
        throw std::logic_error("invalid cmd");
        return;
      }
      out << rmecho(vector, polygon) << '\n';
      return;
    }
    else if (operation == "SAME")
    {
      Polygon polygon;
      in >> polygon;
      if (!in)
      {
        in.setstate(std::ios::failbit);
        throw std::logic_error("invalid cmd");
        return;
      }
      out << same(vector, polygon) << '\n';
      return;
    }
    else
    {
      in.setstate(std::ios::failbit);
      throw std::logic_error("invalid cmd");
      return;
    }
  }
}
double poly::getTotalArea(const std::vector<Polygon>& vector, bool type)
{
  struct calcArea
  {
    double operator()(bool r, double total, const Polygon& polygon)
    {
      if (polygon.polygon_.size() % 2 == r)
      {
        return total+getPolyArea(polygon);
      }
      else
      {
        return total;
      }
    }
  };
  double totalArea = std::accumulate(
    vector.begin(),
    vector.end(),
    0.0,
    std::bind(
      calcArea(),
      type,
      std::placeholders::_1,
      std::placeholders::_2
    )
  );
  return totalArea;
}
double poly::getMeanArea(const std::vector<Polygon>& vector)
{
  struct calcArea
  {
    double operator()(double total,const Polygon& polygon)
    {
      return total+getPolyArea(polygon);
    }
  };
  double area = std::accumulate(
    vector.begin(),
    vector.end(),
    0.0,
    std::bind(
      calcArea(),
      std::placeholders::_1,
      std::placeholders::_2
    )
  );
  return area/(static_cast<double>(vector.size()));
}
double poly::getSpecArea(const std::vector<Polygon>& vector, size_t num)
{
  struct calcArea
  {
    double operator()(size_t size, double total, const Polygon& polygon)
    {
      if (polygon.polygon_.size() == size)
      {
        return total+getPolyArea(polygon);
      }
      else
      {
        return total;
      }
    }
  };
  double totalArea = std::accumulate(
    vector.begin(),
    vector.end(),
    0.0,
    std::bind(
      calcArea(),
      num,
      std::placeholders::_1,
      std::placeholders::_2
    )
  );
  return totalArea;
}
double poly::getMaxArea(const std::vector<Polygon>& vector)
{
  struct Comparator
  {
    double operator()(double max,const Polygon& polygon)
    {
      double area = getPolyArea(polygon);
      if (area > max)
      {
        return area; 
      }
      else
      {
        return max;
      }
    }
  };
  double max = std::accumulate(
    vector.begin(),
    vector.end(),
    0.0,
    Comparator()
  );
  return max;
}
size_t poly::getMaxVert(const std::vector<Polygon>& vector)
{
  struct Comparator
  {
    size_t operator()(size_t max,const Polygon& polygon)
    {
      if (polygon.polygon_.size() > max)
      {
        return polygon.polygon_.size(); 
      }
      else
      {
        return max;
      }
    }
  };
  size_t max = std::accumulate(
    vector.begin(),
    vector.end(),
    0,
    Comparator()
  );
  return max;
}
double poly::getMinArea(const std::vector<Polygon>& vector)
{
  struct Comparator
  {
    double operator()(double min,const Polygon& polygon)
    {
      double area = getPolyArea(polygon);
      if (area < min)
      {
        return area; 
      }
      else
      {
        return min;
      }
    }
  };
  double min = std::accumulate(
    vector.begin(),
    vector.end(),
    std::numeric_limits<double>::max(),
    Comparator()
  );
  return min;
}
size_t poly::getMinVert(const std::vector<Polygon>& vector)
{
  struct Comparator
  {
    size_t operator()(size_t min,const Polygon& polygon)
    {
      if (polygon.polygon_.size() < min)
      {
        return polygon.polygon_.size(); 
      }
      else
      {
        return min;
      }
    }
  };
  size_t min = std::accumulate(
    vector.begin(),
    vector.end(),
    std::numeric_limits<size_t>::max(),
    Comparator()
  );
  return min;
}
size_t poly::countTotal(const std::vector<Polygon>& vector, bool type)
{
  struct Calc
  {
    double operator()(bool r, double total, const Polygon& polygon)
    {
      if (polygon.polygon_.size() % 2 == r)
      {
        return ++total;
      }
      else
      {
        return total;
      }
    }
  };
  size_t amount = std::accumulate(
    vector.begin(),
    vector.end(),
    0,
    std::bind(
      Calc(),
      type,
      std::placeholders::_1,
      std::placeholders::_2
    )
  );
  return amount;
}
size_t poly::countSpec(const std::vector<Polygon>& vector,size_t num)
{
  struct Calc
  {
    double operator()(size_t number, size_t total, const Polygon& polygon)
    {
      if (polygon.polygon_.size() == number)
      {
        return ++total;
      }
      else
      {
        return total;
      }
    }
  };
  double amount = std::accumulate(
    vector.begin(),
    vector.end(),
    0,
    std::bind(
      Calc(),
      num,
      std::placeholders::_1,
      std::placeholders::_2
    )
  );
  return amount;
}
size_t poly::rmecho(std::vector<Polygon>& vector, const Polygon& plg)
{
  bool flag = false;
  size_t counter = 0;
  vector.erase(
    std::remove_if(
      vector.begin(),
      vector.end(),
      [&counter,&flag,plg](const Polygon& current)
      {
        if (!flag && plg == current)
        {
          flag = true;
          return false;
        }
        else if (flag && current == plg)
        {
          counter++;
          return true;
        }
        else if (flag && !(current == plg))
        {
          flag = false;
          return false;
        }
        else {
          return false;
        }
      }
    ),
    vector.end()
  );
  return counter;
}
size_t poly::same(const std::vector<Polygon>& vector, const Polygon& plg)
{
  struct directionalVector
  {
    int x_;
    int y_;
  };
  struct pointComp
  {
    bool operator()(const directionalVector& dir, const Point& point1, const Point& point2)
    {
      return (dir.x_==(point1.x_-point2.x_)) && (dir.y_==(point1.y_-point2.y_));
    }
  };
  size_t counter = std::accumulate(
    vector.begin(),
    vector.end(),
    0,
    [&plg](size_t total, const Polygon& poly)
    {
      if (plg.polygon_.size()!=poly.polygon_.size())
      {
        return total;
      }
      else
      {
        directionalVector direction = {
          plg.polygon_[0].x_-poly.polygon_[0].x_,
          plg.polygon_[0].y_-poly.polygon_[0].y_
        };
        if (std::equal(
            plg.polygon_.cbegin(),
            plg.polygon_.cend(),
            poly.polygon_.cbegin(),
            poly.polygon_.cend(),
            std::bind(pointComp(),direction,std::placeholders::_1,std::placeholders::_2)
          )
        )
        {
          return ++total;
        }
        else
        {
          return total;
        }
      } 
    }
  );
  return counter;
}

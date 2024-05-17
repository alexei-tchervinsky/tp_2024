#include "polygon.h"

namespace poly
{
  Point::Point():
    x_(0),
    y_(0)
  {};
  Point::Point(int x, int y):
    x_(x),
    y_(y)
  {};
  std::istream& operator>>(std::istream& in, Point& point)
  {
    std::istream::sentry ward(in);
    if (!ward)
    {
      return in;
    }
    in >> DefInput{ '(' } >> point.x_;
    in >> DefInput{ ';' } >> point.y_ >> DefInput{ ')' };
    if (!in)
    {
      in.setstate(std::ios::failbit);
      throw std::logic_error("invalid input");
      return in;
    }
    return in;
  }
  std::istream& operator>>(std::istream& in, PointIO&& ptr)
  {
    std::istream::sentry ward(in);
    if (!ward)
    {
      return in;
    }
    return in >> ptr.ref;
  }
  bool operator==(const Point& first, const Point& second)
  {
    return (first.x_==second.x_) && (first.y_==second.y_);
  }
  std::ostream& operator<<(std::ostream& out, const Point& point)
  {
    std::ostream::sentry ward(out);
    iofmtguard guard(out);
    if (!ward)
    {
      return out;
    }
    out << '(' << point.x_ << ';' << point.y_ << ')';
    return out;
  }
  std::istream& operator>>(std::istream& in, Polygon& polyg)
  {
    std::istream::sentry ward(in);
    if (!ward)
    {
      return in;
    }
    int ofVert = 0;
    {
      using number = NumberInput;
      using expr = DefInput;
      in >> number{ ofVert };
      if (!in || ofVert<=2)
      {
        in.setstate(std::ios::failbit);
        throw std::logic_error("invalid input");
        return in;
      }
      Point ipoint;
      std::vector<Point> ivector;
      for (size_t i = 0; i<ofVert; i++)
      {
        if (in >> ipoint)
        {
          ivector.push_back(ipoint);
        }
      }
      if (in && ivector.size() == ofVert && (in.get() == '\n'))
      {
        polyg = Polygon{ ivector };
      }
      else
      {
        throw std::logic_error("errored");
        in.setstate(std::ios::failbit);
        return in;
      }
    }
    return in;
  }
  std::ostream& operator<<(std::ostream& out, const Polygon& polyg)
  {
    std::ostream::sentry ward(out);
    if (!ward)
    {
      return out;
    }
    iofmtguard guard(out);
    for (Point i : polyg.polygon_)
    {
      out << i << ' ';
    }
    return out;
  }
  bool operator==(const Polygon& first, const Polygon& second)
  {
    if (first.polygon_.size()!=second.polygon_.size())
    {
      return false;
    }
    for (size_t i = 0; i<first.polygon_.size(); i++)
    {
      if (!(first.polygon_[i]==second.polygon_[i]))
      {
        return false;
      }
    }
    return true;
  }
  double getPolyArea(const Polygon& polygon)
  {
    struct determine
    {
      double operator()(const Point& point1, const Point& point2)
      {
        return std::abs((point2.x_*point1.y_)-(point2.y_*point1.x_));
      }
    };
    std::vector<double> subAreas(polygon.polygon_.size());
    std::transform(
      ++polygon.polygon_.begin(),
      polygon.polygon_.end(),
      polygon.polygon_.begin(),
      subAreas.begin(),
      std::bind(determine(),std::placeholders::_1,std::placeholders::_2)
    );
    double area = std::accumulate(
      subAreas.begin(),
      subAreas.end(),
      0.0
    );
    double wrapped = determine()(
      polygon.polygon_[polygon.polygon_.size()-1],
      polygon.polygon_[0]
    );
    return std::abs((area + wrapped)) / 2.0;
  }
  std::istream& operator>>(std::istream& in, DefInput&& def)
  {
    std::istream::sentry ward(in);
    if (!ward)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != def.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream& operator>>(std::istream& in, NumberInput&& num)
  {
    std::istream::sentry ward(in);
    if (!ward)
    {
      return in;
    }
    return in >> num.ref;
  }
  iofmtguard::iofmtguard(std::basic_ios<char>& s):
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {};
  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}

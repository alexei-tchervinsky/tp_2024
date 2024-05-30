#include "io.h"

bool berezneva::isPoint(const std::string& str)
{
  std::regex pattern("\\(-?[0-9]+;-?[0-9]+\\)");
  return std::regex_match(str, pattern);
}

std::ostream& berezneva::operator<<(std::ostream& out, const berezneva::Point& point)
{
  return (out << '(' << point.x_ << ';' << point.y_ << ')');
}

std::ostream& berezneva::operator<<(std::ostream& out, const berezneva::Polygon& polygon)
{
  out << polygon.points_.size();
  for (auto& p : polygon.points_)
    out << ' ' << p;
  return (out << '\n');
}

std::istream& berezneva::operator>>(std::istream& in, berezneva::Point& point)  // (1;1)
{
  std::istream::sentry sentry(in);

  if (!sentry)
    return in;

  std::string str;
  in >> str;
  if (!berezneva::isPoint(str))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  char ch;
  std::stringstream ss(str);
  ss >> ch >> point.x_ >> ch >> point.y_ >> ch;
  return in;
}


std::istream& berezneva::operator>>(std::istream& in, berezneva::Polygon& polygon)  // 3 (1;2) (0;0) (0;3)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  polygon.points_.clear();
  std::size_t n;
  in >> n;
  if (in.fail() || n < 3)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  polygon.points_.resize(n);

  for (auto& p : polygon.points_)
  {
    if (in.peek() == '\n')
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    in >> p;
  }
  if (in.peek() != '\n')
    in.setstate(std::ios_base::failbit);
  return in;
}

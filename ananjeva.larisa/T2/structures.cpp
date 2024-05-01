#include"structures.hpp"
#include"delimiter.hpp"
#include<iomanip>

std::istream& ananjeva::operator>>(std::istream& in, DoubleIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  if (!(in >> dest.ref)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& ananjeva::operator>>(std::istream& in, CharIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  if (!(in >> DelimiterIO{ '\'' } >> dest.ref >> DelimiterIO{ '\'' }) ||
    (!std::isalpha(dest.ref))) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& ananjeva::operator>>(std::istream& in, StringIO&& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::ostream& ananjeva::outputDoubleScience(std::ostream& out, double number) {
  int mantissa = 0;
  int degree = 0;
  char sign = '0';
  if (number >= 1.0) {
    while (number >= 10.0) {
      number /= 10;
      degree++;
    }
    sign = '+';
  }
  else {
    while (number < 1.0) {
      number *= 10;
      degree++;
    }
    sign = '-';
  }
  out << std::fixed << std::setprecision(2) << number << 'e' << sign << degree;
  return out;
}
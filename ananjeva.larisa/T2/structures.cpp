#include "structures.hpp"
#include "delimiter.hpp"
#include <iomanip>
#include <cmath>

std::istream& ananjeva::operator>>(std::istream& in, DoubleIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  int mantissaBegin = 0;
  int mantissaEnd = 0;
  std::string mantissaEndStr = "";
  int degree = 0;
  char letter = '0';
  std::size_t zeroCounter = 0;
  in >> mantissaBegin >> DelimiterIO{ '.' };
  while (in.peek() == '0') {
    zeroCounter += 1;
    in.get(letter);
  }
  if (in.peek() != 'e' && in.peek() != 'E') {
    in >> mantissaEnd;
  }
  mantissaEndStr = std::to_string(mantissaEnd);
  letter = in.peek();
  if (letter == 'e') {
    in >> DelimiterIO{ 'e' };
  }
  else {
    in >> DelimiterIO{ 'E' };
  }
  in >> degree;
  dest.ref = (mantissaBegin + mantissaEnd * pow(0.1, zeroCounter + (mantissaEndStr.length()))) * pow(10, degree);
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
  int degree = 0;
  char sign = '0';
  if (number == 0.0) {
    sign = '+';
  }
  else if (number >= 1.0) {
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
  out << std::fixed << std::setprecision(1) << number << 'e' << sign << degree;
  return out;
}

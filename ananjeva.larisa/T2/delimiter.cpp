#include"delimiter.hpp"
#include"structures.hpp"

std::istream& ananjeva::operator>>(std::istream& in, DelimiterIO&& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.expected)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& ananjeva::operator>>(std::istream& in, LabelIO&& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  std::string data = "";
  if ((in >> StringIO{ data }) && (data != dest.expected)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}
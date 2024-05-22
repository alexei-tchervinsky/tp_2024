#include "dataStruct.hpp"
#include "delimiter.hpp"

std::istream& ananjeva::operator>>(std::istream& in, EngIO&& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  std::string readStr = "";
  in >> readStr;
  if (in) {
    dest.eng = readStr;
  }
  return in;
}

std::istream& ananjeva::operator>>(std::istream& in, RusIO&& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  std::string readStr = "";
  char readChar = '0';
  while (in && in.peek() != '}') {
    while (in.peek() != ';' && in.peek() != '}') {
      in >> readChar;
      if (readChar == '\n' or readChar == '\0') {
        in.setstate(std::ios::failbit);
      }
      readStr += readChar;
    }
    if (in.peek() != '}') {
      in >> DelimiterIO{ ';' };
    }

    dest.rus.insert(readStr);
    readStr = "";
  }
  return in;
}

std::istream& ananjeva::operator>>(std::istream& in, DictIO& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  DictIO readStr;
  in >> DelimiterIO{ '{' };
  in >> EngIO{ readStr.dictStr.first };
  in >> DelimiterIO{ '-' };
  in >> RusIO{ readStr.dictStr.second };
  in >> DelimiterIO{ '}' };
  if (!in) {
      in.setstate(std::ios::failbit);
  }
  else {
    dest = readStr;
  }
  return in;
}

#include "io.hpp"

std::istream& berezneva::operator>>(std::istream& in, En&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  std::string str;
  in >> str;

  if (in)
    dest.en_ = str;

  return in;
}

std::istream& berezneva::operator>>(std::istream& in, Rus&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  std::string str;
  char c;

  while (in && in.peek() != '}')
  {
    while (in.peek() != ';' && in.peek() != '}')
    {
      in >> c;

      if (c == '\n' or c == '\0')
        in.setstate(std::ios::failbit);

      str += c;
    }

    if (in.peek() != '}')
      in >> Delimiter{ ';' };

    dest.rus_.insert(str);
    str = "";
  }

  return in;
}

std::istream& berezneva::operator>>(std::istream& in, Dict& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  Dict str;
  in >> Delimiter{ '{' };
  in >> En{ str.str_.first };
  in >> Delimiter{ '-' };
  in >> Rus{ str.str_.second };
  in >> Delimiter{ '}' };

  if (!in)
    in.setstate(std::ios::failbit);
  else
    dest = str;

  return in;
}

std::istream& berezneva::operator>>(std::istream& in, Delimiter&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  char c = '0';
  in >> c;

  if (in && (c != dest.expected_))
    in.setstate(std::ios::failbit);

  return in;
}

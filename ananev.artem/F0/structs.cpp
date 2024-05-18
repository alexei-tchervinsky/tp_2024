#include "Structs.hpp"

namespace structs
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '\0';
    in >> c;
    if (in && (c != dest.del))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, EnglishIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string temp;
    in >> temp;
    if (in)
    {
      dest.eng = temp;
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, RussianIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string temp;
    in >> temp;
    char c = temp.back();
    while (in && (c != '}'))
    {
      if (c == '\n' || c == '\0')
      {
        in.setstate(std::ios::failbit);
        return in;
      }
      dest.rus.insert(temp);
      in >> temp;
      c = temp.back();
    }
    temp.pop_back();
    dest.rus.insert(temp);
    return in;

  }
  std::istream &operator>>(std::istream &in, DictIO &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DictIO temp;
    in >> DelimiterIO{'{'};
    in >> EnglishIO{temp.dict_el.first};
    in >> DelimiterIO{'-'};
    in >> RussianIO{temp.dict_el.second};
    if (in)
    {
      dest = temp;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
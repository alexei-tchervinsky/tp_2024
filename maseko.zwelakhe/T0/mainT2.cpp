#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <algorithm>

namespace nspace
{
  struct Data
  {
    double key1;
    long long key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleIO
  {
    double& ref;
  };

  struct LongLIO
  {
    long long& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct LabelIO
  {
    std::string exp;
  };

  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, DoubleIO&& dest);
  std::istream& operator>>(std::istream& in, LongLIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, Data& dest);
  std::ostream& operator<<(std::ostream& out, const Data& dest);
}

namespace nspace
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, DoubleIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{ 'D' };
  }

  std::istream& operator>>(std::istream& in, LongLIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Data& data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
      return in;

    std::string input;
    if (!std::getline(in, input, ')'))
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    std::istringstream iss(input + ')');
    char c;
    if (!(iss >> c) || c != '(')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    while (iss >> c)
    {
      if (c == ':')
      {
        std::string key;
        if (!(iss >> key))
        {
          in.setstate(std::ios::failbit);
          return in;
        }

        if (key == "key1")
        {
          if (!(iss >> data.key1) || !(iss >> c) || (c != 'd' && c != 'D'))
          {
            in.setstate(std::ios::failbit);
            return in;
          }
        }
        else if (key == "key2")
        {
          if (!(iss >> data.key2) || !(iss >> c) || (c != 'l' &&
            c != 'L') || !(iss >> c) || (c != 'l' && c != 'L'))
          {
            in.setstate(std::ios::failbit);
            return in;
          }
        }
        else if (key == "key3")
        {
          if (!(iss >> std::quoted(data.key3)))
          {
            in.setstate(std::ios::failbit);
            return in;
          }
        }
      }

      if (iss.peek() == ')')
        break;
    }

    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Data& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(";
    out << ":key1 " << std::fixed << std::setprecision(1) << src.key1 << "d";
    out << ":key2 " << std::fixed << std::setprecision(1) << src.key2 << "ll";
    out << ":key3 " << "\"" << src.key3 << "\"";
    out << ":)";
    return out;
  }

  iofmtguard::iofmtguard(std::basic_ios< char >& s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}

int main()
{
  using nspace::Data;
  std::vector< Data > data;

  while (!std::cin.eof()) {
    std::copy(
      std::istream_iterator< Data >(std::cin),
      std::istream_iterator< Data >(),
      std::back_inserter(data)
    );
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(),
    [](const Data& a, const Data& b) {
      if (a.key1 != b.key1)
      {
        return (a.key1 < b.key1);
      }
      if (a.key2 != b.key2)
      {
        return (a.key2 < b.key2);
      }
      return (a.key3.length() < b.key3.length());
    });

  std::copy(
    data.begin(),
    data.end(),
    std::ostream_iterator< Data >(std::cout, "\n")
  );
  return 0;
}

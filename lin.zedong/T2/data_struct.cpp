#include "data_struct.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace namesp
{
    iofmtguard::iofmtguard(std::basic_ios<char>& s) : s_(s), fill_(s.fill()), precision_(s.precision()), fmt_(s.flags()) {}

    iofmtguard::~iofmtguard()
    {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '\0';
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
        std::string str;
        in >> str;
        if (str.back() != 'd' && str.back() != 'D')
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        str.pop_back();
        dest.ref = std::stod(str);
        return in;
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

    std::istream& operator>>(std::istream& in, LITIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string str;
        in >> str;
        if (str.size() < 3 || str.substr(str.size() - 2) != "ll")
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        str.erase(str.size() - 2);
        dest.ref = std::stoll(str);
        return in;
    }

    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string data;
        if ((in >> StringIO{ data }) && (data != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::string fromDoubleToScientific(double val)
    {
        std::ostringstream oss;
        oss << std::scientific << val << 'd';
        return oss.str();
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input;
        std::string characters;
        {
            using sep = DelimiterIO;
            using lit = LITIO;
            using str = StringIO;
            using dbl = DoubleIO;
            in >> sep{ '(' };
            for (std::size_t i = 0; i < 3; i++)
            {
                in >> sep{ ':' };
                in >> characters;
                if (characters == "key1")
                {
                    in >> dbl{ input.key1 };
                }
                else if (characters == "key2")
                {
                    in >> lit{ input.key2 };
                }
                else
                {
                    in >> str{ input.key3 };
                }
            }
            in >> sep{ ':' };
            in >> sep{ ')' };
        }
        if (in)
        {
            dest = input;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(:key1 " << fromDoubleToScientific(src.key1);
        out << ":key2 " << src.key2 << "ll";
        out << ":key3 \"" << src.key3 << "\":)";
        return out;
    }

    bool Compare::operator()(DataStruct first, DataStruct second) const
    {
        if (first.key1 != second.key1)
        {
            return first.key1 < second.key1;
        }
        if (first.key2 != second.key2)
        {
            return first.key2 < second.key2;
        }
        return first.key3.length() < second.key3.length();
    }
}
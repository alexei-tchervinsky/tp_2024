#include "data_struct.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

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
        char c;
        in >> c;
        if (in && tolower(c) != dest.exp)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DoubleIO&& dest)
    {
        if (std::istream::sentry sentry(in);!sentry)
        {
            return in;
        }
        return in >> dest.ref >> DelimiterIO { 'd' };
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        if (std::istream::sentry sentry(in);!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream& operator>>(std::istream& in, LITIO&& dest)
    {
        if (std::istream::sentry sentry(in);!sentry)
        {
            return in;
        }
        return in >> dest.ref >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
    }

    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        if (std::istream::sentry sentry(in);!sentry)
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
        if (std::istream::sentry sentry(in);!sentry)
        {
            return in;
        }
        DataStruct input;
        {
            using sep = DelimiterIO;
            using lit = LITIO;
            using str = StringIO;
            using dbl = DoubleIO;
            in >> sep{ '(' };
            std::string keyX;
            for (std::size_t i = 0; i < 3; ++i)
            {
                in >> sep{ ':' } >> keyX;
                if (keyX == "key1")
                {
                    in >> dbl{ input.key1 };
                }
                else if (keyX == "key2")
                {
                    in >> lit{ input.key2 };
                }
                else if (keyX == "key3")
                {
                    in >> str{ input.key3 };
                }
                else
                {
                    in.setstate(std::ios::failbit);
                }
            }
            in >> sep{ ':' } >> sep{ ')' };
        }
        if (in)
        {
            dest = input;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
    {
        if (std::ostream::sentry sentry(out);!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(:key1 " << std::fixed << std::setprecision(1) << dest.key1 << " "
        << ":key2 " << dest.key2 << "ll "
        << ":key3 " << '"' << dest.key3 << '"' << ":)";
        return out;
    }

    bool operator<(const DataStruct& first, const DataStruct& second)
    {
        if (first.key1 != second.key1)
        {
            return first.key1 < second.key1;
        }
        if (first.key2 != second.key2)
        {
            return first.key2 < second.key2;
        }
        return first.key3.size() < second.key3.size();
    }
}

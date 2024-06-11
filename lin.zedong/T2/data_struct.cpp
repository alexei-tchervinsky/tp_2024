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
        char c = '0';
        in >> c;
        c = tolower(c);
        if (in && (c != dest.exp))
        {
            in.setstate(std::ios::failbit);
            std::cerr << "Error: Expected delimiter '" << dest.exp << "' but got '" << c << "'\n"; //
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
         if (!(in >> dest.ref))
        {
            in.setstate(std::ios::failbit);
            std::cerr << "Error: Invalid input for double type\n";
        }
        else if (!(in >> DelimiterIO { 'd' }))
        {
            std::cerr << "Error: Expected 'd' after double value\n";
        }
        return in;
        //in >> dest.ref;
        //return in >> DelimiterIO { 'd' };
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        if (!std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"'))
        {
            in.setstate(std::ios::failbit);
            std::cerr << "Error: Invalid input for string type\n";
        }
        return in;
        //return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream& operator>>(std::istream& in, LITIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        if (!(in >> dest.ref))
        {
            in.setstate(std::ios::failbit);
            std::cerr << "Error: Invalid input for long long type\n";
        }
        else if (!(in >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' }))
        {
            std::cerr << "Error: Expected 'll' after long long value\n";
        }
        return in;
        //in >> dest.ref;
        //return in >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
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
            std::cerr << "Error: Expected label '" << dest.exp << "' but got '" << data << "'\n"; //
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
                    std::cerr << "Error: Unknown key '" << keyX << "'\n"; //
                }
            }
            in >> sep{ ':' } >> sep{ ')' };
        }
        if (in)
        {
            dest = input;
        }
        else  //
        {
            std::cerr << "Error: Invalid input format for DataStruct\n";
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
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

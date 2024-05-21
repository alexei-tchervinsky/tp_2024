#include "data_struct.h"
#include <iomanip>

namespace mungoi
{
    std::istream& operator>>(std::istream& in, DoubleIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.d;
    }

    std::istream& operator>>(std::istream& in, LongLongIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.ll;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> std::ws, dest.str, '"');
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        iofmtguard fmtguard(in);
        DataStruct input;
        std::string curr;
        in >> std::ws >> curr;

        if (curr != "(:key1")
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        in >> DoubleIO{ input.key1 } >> curr;
        if (curr != ":key2")
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        in >> LongLongIO{ input.key2 } >> curr;
        if (curr != ":key3")
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        in >> std::quoted(input.key3) >> curr;
        if (curr != ":)")
        {
            in.setstate(std::ios::failbit);
            return in;
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
        out << "(:key1 " << src.key1 << ":key2 " << src.key2 << ":key3 \"" << src.key3 << "\":)";
        return out;
    }

    bool operator<(const DataStruct& a, const DataStruct& b)
    {
        if (a.key1 != b.key1)
        {
            return a.key1 < b.key1;
        }
        if (a.key2 != b.key2)
        {
            return a.key2 < b.key2;
        }
        return a.key3.size() < b.key3.size();
    }

    iofmtguard::iofmtguard(std::basic_ios<char>& s) :
        s_(s),
        fill_(s.fill()),
        precision_(s.precision()),
        fmt_(s.flags())
    {
    }

    iofmtguard::~iofmtguard()
    {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }
}

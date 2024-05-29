#include "Datastruct.hpp"
#include <cctype>
#include "scopeguard.hpp"

std::istream& bredyuk::operator>>(std::istream& is, DelimiterIO&& dest)
{
    std::istream::sentry guard(is);
    if (!guard)
    {
        return is;
    }
    char c = '0';
    is >> c;
    c = tolower(c);
    if (is && (c != dest.exp))
    {
        is.setstate(std::ios::failbit);
    }
    return is;
}

std::istream& bredyuk::operator>>(std::istream& is, DoubleIO&& dest)
{
    std::istream::sentry guard(is);
    if (!guard)
    {
        return is;
    }
    if (!(is >> dest.ref >> DelimiterIO{ 'd' }) && !std::isdigit(dest.ref))
    {
        is.setstate(std::ios::failbit);
    }
    return is;
}

std::istream& bredyuk::operator>>(std::istream& is, UnsignedLongLongIO&& dest)
{
    std::istream::sentry guard(is);
    if (!guard)
    {
        return is;
    }
    if (!(is >> dest.ref >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' }) && !std::isdigit(dest.ref))
    {
        is.setstate(std::ios::failbit);
    }
    return is;
}

std::istream& bredyuk::operator>>(std::istream& is, StringIO&& dest)
{
    std::istream::sentry guard(is);
    if (!guard)
    {
        return is;
    }
    return std::getline(is >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& bredyuk::operator>>(std::istream& is, DataStruct& dest)
{
    std::istream::sentry guard(is);
    if (!guard)
    {
        return is;
    }
    DataStruct input;
    {
        using sep = DelimiterIO;
        using dbl = DoubleIO;
        using ull = UnsignedLongLongIO;
        using str = StringIO;
        is >> sep{ '(' };
        std::string keyX;
        for (size_t i = 0; i < 3 && is; ++i)
        {
            is >> sep{ ':' } >> keyX;
            if (keyX == "key1")
            {
                is >> dbl{ input.key1 };
            }
            else if (keyX == "key2")
            {
                is >> ull{ input.key2 };
            }
            else if (keyX == "key3")
            {
                is >> str{ input.key3 };
            }
            else
            {
                is.setstate(std::ios::failbit);
            }
        }
        is >> sep{ ':' } >> sep{ ')' };
    }
    if (is)
    {
        dest = input;
    }
    return is;
}

std::ostream& bredyuk::operator<<(std::ostream& out, const DataStruct& src)
{
    std::ostream::sentry guard(out);
    if (!guard)
    {
        return out;
    }
    iofmtguard fmtguard(out);
    out << "(:";
    out << "key1 " << std::fixed << std::setprecision(1) << src.key1 << "d:";
    out << "key2 " << src.key2 << "ull:";
    out << "key3 " << std::quoted(src.key3) << ":)";
    return out;
}

bool bredyuk::operator<(const DataStruct& lhs, const DataStruct& rhs)
{
    if (lhs.key1 != rhs.key1)
    {
        return lhs.key1 < rhs.key2;
    }

    if (lhs.key2 != rhs.key2)
    {
        return lhs.key2 < rhs.key2;
    }

    return lhs.key3.size() < rhs.key3.size();
}
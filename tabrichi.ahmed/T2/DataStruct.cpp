#include "DataStruct.hpp"
#include "Fmtguard.hpp"

namespace TahMed
{
    std::string toBinary(unsigned long long number)
    {
        std::string result = "";
        unsigned long long temp_ = number;

        if (temp_ == 0)
        {
            result = "0";
        }
        if (temp_ == 1)
        {
            return "01";
        }
        while (temp_ != 0)
        {
            result = std::to_string(temp_ % 2) + result;
            temp_ = temp_ / 2;
        }
        return result;
    }

    unsigned long long BinaryToDecimal(unsigned long long binValue)
    {
        unsigned long long result = 0;
        for (unsigned long long i = 1; binValue; binValue /= 10, i *= 2)
        {
            result += i * (binValue % 10);
        }
        return result;
    }

    std::istream& operator>>(std::istream& inStream, DelimiterIO&& delimiter)
    {
        std::istream::sentry sentry(inStream);
        if (!sentry)
        {
            return inStream;
        }
        char c = '\0';
        inStream >> c;
        if (inStream && (c != delimiter.del))
        {
            inStream.setstate(std::ios::failbit);
        }
        return inStream;
    }

    std::istream& operator>>(std::istream& in, LITIO&& literal)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> std::dec >> literal.lit;
        if (in.peek() == 'U')
        {
            return in >> DelimiterIO{ 'U' } >> DelimiterIO{ 'L' } >> DelimiterIO{ 'L' };
        }
        else
        {
            return in >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
        }
    }

    std::istream& operator>>(std::istream& in, BINIO&& binary)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> DelimiterIO{ '0' };
        if (in.peek() == 'B')
        {
            in >> DelimiterIO{ 'B' };
        }
        else
        {
            in >> DelimiterIO{ 'b' };
        }
        unsigned long long bin = 0;
        in >> bin;
        binary.bin = BinaryToDecimal(bin);
        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& stringData)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, stringData.str, '"');
    }

    std::istream& operator>>(std::istream& in, LabelIO&& labelData)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string data = "";
        if ((in >> StringIO{ data }) && (data != labelData.lab))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DataItem& theIinput)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataItem input;
        std::string chars;

        in >> DelimiterIO{ '(' };
        for (std::size_t i = 0; i < 3; ++i)
        {
            in >> DelimiterIO{ ':' };
            in >> chars;
            if (chars == "key1")
            {
                in >> LITIO{ input.key1 };
            }
            else if (chars == "key2")
            {
                in >> BINIO{ input.key2 };
            }
            else
            {
                in >> StringIO{ input.key3 };
            }
        }
        in >> DelimiterIO{ ':' };
        in >> DelimiterIO{ ')' };
        if (in)
        {
            theIinput = input;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataItem& output)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        Fmtguard fmtguard(out);
        out << "(:key1 " << output.key1 << "ull";
        out << ":key2 0b" << toBinary(output.key2);
        out << ":key3 \"" << output.key3 << "\":)";
        return out;
    }
}
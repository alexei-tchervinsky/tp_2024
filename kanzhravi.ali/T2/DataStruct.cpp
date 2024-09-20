#include "DataStruct.hpp"
#include "Guard.hpp"

namespace AliKN {

    std::string toBinary(unsigned long long number) {
        std::string result = "";
        unsigned long long temp = number;

        if (temp == 0) {
            result = "0";
        }

        if (temp == 1) {
            return "01";
        }

        while (temp != 0) {
            result = std::to_string(temp % 2) + result;
            temp /= 2;
        }

        return result;
    }

    unsigned long long binaryToDecimal(unsigned long long binValue) {
        unsigned long long res = 0;
        for (unsigned long long i = 1; binValue; binValue /= 10, i *= 2) {
            res += i * (binValue % 10);
        }
        return res;
    }

    std::istream& operator>>(std::istream& inStream, DelimIO&& delimiter) {
        std::istream::sentry sentry(inStream);
        if (!sentry) return inStream;

        char temp = '\0';
        inStream >> temp;
        if (inStream && (temp != delimiter.del)) {
            inStream.setstate(std::ios::failbit);
        }
        return inStream;
    }

    std::istream& operator>>(std::istream& inStream, LiteralIO&& literal) {
        std::istream::sentry sentry(inStream);
        if (!sentry) return inStream;

        inStream >> std::dec >> literal.lit;
        if (inStream.peek() == 'U') {
            return inStream >> DelimIO{ 'U' } >> DelimIO{ 'L' } >> DelimIO{ 'L' };
        }
        return inStream >> DelimIO{ 'u' } >> DelimIO{ 'l' } >> DelimIO{ 'l' };
    }

    std::istream& operator>>(std::istream& inStream, BinaryIO&& binary) {
        std::istream::sentry sentry(inStream);
        if (!sentry) return inStream;

        inStream >> DelimIO{ '0' };
        if (inStream.peek() == 'B') {
            inStream >> DelimIO{ 'B' };
        }
        else {
            inStream >> DelimIO{ 'b' };
        }

        unsigned long long bin = 0;
        inStream >> bin;
        binary.bin = binaryToDecimal(bin);
        return inStream;
    }

    std::istream& operator>>(std::istream& inStream, StrIO&& stringData) {
        std::istream::sentry sentry(inStream);
        if (!sentry) return inStream;

        return std::getline(inStream >> DelimIO{ '"' }, stringData.str, '"');
    }

    std::istream& operator>>(std::istream& inStream, LabelIO&& labelData) {
        std::istream::sentry sentry(inStream);
        if (!sentry) return inStream;

        std::string temp;
        if ((inStream >> StrIO{ temp }) && (temp != labelData.label)) {
            inStream.setstate(std::ios::failbit);
        }
        return inStream;
    }

    std::istream& operator>>(std::istream& inStream, DataItem& input) {
        std::istream::sentry sentry(inStream);
        if (!sentry) return inStream;

        DataItem data;
        std::string buffer;

        inStream >> DelimIO{ '(' };
        for (std::size_t i = 0; i < 3; ++i) {
            inStream >> DelimIO{ ':' };
            inStream >> buffer;

            if (buffer == "attr1") {
                inStream >> LiteralIO{ data.attr1 };
            }
            else if (buffer == "attr2") {
                inStream >> BinaryIO{ data.attr2 };
            }
            else {
                inStream >> StrIO{ data.attr3 };
            }
        }
        inStream >> DelimIO{ ':' };
        inStream >> DelimIO{ ')' };

        if (inStream) {
            input = data;
        }

        return inStream;
    }

    std::ostream& operator<<(std::ostream& outStream, const DataItem& output) {
        std::ostream::sentry sentry(outStream);
        if (!sentry) return outStream;

        Guard Guard(outStream);
        outStream << "(:attr1 " << output.attr1 << "ull";
        outStream << ":attr2 0b" << toBinary(output.attr2);
        outStream << ":attr3 \"" << output.attr3 << "\":)";
        return outStream;
    }
}

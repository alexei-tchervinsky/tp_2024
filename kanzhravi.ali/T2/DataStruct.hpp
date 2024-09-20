#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>

namespace AliKN {

    struct DataItem {
        unsigned long long attr1;
        unsigned long long attr2;
        std::string attr3;
    };

    struct DelimIO {
        char del;
    };

    struct LiteralIO {
        unsigned long long& lit;
    };

    struct BinaryIO {
        unsigned long long& bin;
    };

    struct StrIO {
        std::string& str;
    };

    struct LabelIO {
        std::string label;
    };

    std::istream& operator>>(std::istream& inStream, DelimIO&& delimiter);
    std::istream& operator>>(std::istream& inStream, LiteralIO&& literal);
    std::istream& operator>>(std::istream& inStream, BinaryIO&& binary);
    std::istream& operator>>(std::istream& inStream, StrIO&& stringData);
    std::istream& operator>>(std::istream& inStream, LabelIO&& labelData);
    std::istream& operator>>(std::istream& inStream, DataItem& input);
    std::ostream& operator<<(std::ostream& outStream, const DataItem& output);
    std::string toBinary(unsigned long long number);

}

#endif

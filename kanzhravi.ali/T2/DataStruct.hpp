#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>

namespace AliKN {
    struct DataStruct {
        unsigned long long key1;
        unsigned long long key2;
        std::string key3;
    };

    struct Delimiter {
        char delimiter;
    };

    struct Literal {
        unsigned long long& literal;
    };

    struct Binary {
        unsigned long long& binary;
    };

    struct StringField {
        std::string& str;
    };

    struct Label {
        std::string label;
    };

    std::istream& operator>>(std::istream& in, Delimiter&& delimiter);
    std::istream& operator>>(std::istream& in, Literal&& literal);
    std::istream& operator>>(std::istream& in, Binary&& binary);
    std::istream& operator>>(std::istream& in, StringField&& strField);
    std::istream& operator>>(std::istream& in, Label&& label);
    std::istream& operator>>(std::istream& in, DataStruct& data);
    std::ostream& operator<<(std::ostream& out, const DataStruct& data);
    std::string toBinary(unsigned long long value);
}

#endif

#include "DataStruct.hpp"
#include "Guard.hpp"

namespace AliKN {
    std::string toBinary(unsigned long long value) {
        std::string binary = "";
        if (value == 0) {
            return "0";
        }
        while (value != 0) {
            binary = std::to_string(value % 2) + binary;
            value /= 2;
        }
        return binary;
    }

    unsigned long long binaryToDecimal(unsigned long long binary) {
        unsigned long long decimal = 0;
        for (unsigned long long factor = 1; binary; binary /= 10, factor *= 2) {
            decimal += factor * (binary % 10);
        }
        return decimal;
    }

    std::istream& operator>>(std::istream& in, Delimiter&& delimiter) {
        char c = '\0';
        in >> c;
        if (in && (c != delimiter.delimiter)) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, Literal&& literal) {
        in >> std::dec >> literal.literal;
        if (in.peek() == 'U') {
            return in >> Delimiter{ 'U' } >> Delimiter{ 'L' } >> Delimiter{ 'L' };
        }
        else {
            return in >> Delimiter{ 'u' } >> Delimiter{ 'l' } >> Delimiter{ 'l' };
        }
    }

    std::istream& operator>>(std::istream& in, Binary&& binary) {
        in >> Delimiter{ '0' };
        if (in.peek() == 'B') {
            in >> Delimiter{ 'B' };
        }
        else {
            in >> Delimiter{ 'b' };
        }
        unsigned long long bin = 0;
        in >> bin;
        binary.binary = binaryToDecimal(bin);
        return in;
    }

    std::istream& operator>>(std::istream& in, StringField&& strField) {
        return std::getline(in >> Delimiter{ '"' }, strField.str, '"');
    }

    std::istream& operator>>(std::istream& in, Label&& label) {
        std::string data = "";
        if ((in >> StringField{ data }) && (data != label.label)) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DataStruct& data) {
        DataStruct temp;
        std::string key;
        in >> Delimiter{ '(' };
        for (std::size_t i = 0; i < 3; ++i) {
            in >> Delimiter{ ':' };
            in >> key;
            if (key == "key1") {
                in >> Literal{ temp.key1 };
            }
            else if (key == "key2") {
                in >> Binary{ temp.key2 };
            }
            else {
                in >> StringField{ temp.key3 };
            }
        }
        in >> Delimiter{ ':' };
        in >> Delimiter{ ')' };
        if (in) {
            data = temp;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
        iofmtguard guard(out);
        out << "(:key1 " << data.key1 << "ull";
        out << ":key2 0b" << toBinary(data.key2);
        out << ":key3 \"" << data.key3 << "\":)";
        return out;
    }
}

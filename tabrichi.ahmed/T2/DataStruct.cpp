#include "DataStruct.hpp"
#include <sstream>
#include <stdexcept>
#include <bitset>
#include <algorithm>
#include <cctype>

unsigned long long parseBinary(const std::string& binaryStr) {
    if (binaryStr.rfind("0b", 0) == 0 || binaryStr.rfind("0B", 0) == 0) {
        return std::bitset<64>(binaryStr.substr(2)).to_ullong();
    }
    throw std::invalid_argument("Invalid binary format: " + binaryStr);
}

unsigned long long parseULL(const std::string& str) {
    if (str.back() == 'l' || str.back() == 'L') {
        return std::stoull(str.substr(0, str.size() - 3));
    }
    return std::stoull(str);
}

std::istream& operator>>(std::istream& is, DataStruct& data) {
    std::string input;
    std::getline(is, input);

    if (input.empty() || input.front() != '(' || input.back() != ')') {
        is.setstate(std::ios::failbit);
        return is;
    }

    input = input.substr(1, input.size() - 2);

    std::istringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ':')) {
        std::string key, value;
        std::istringstream tokenStream(token);
        tokenStream >> key >> value;

        if (key == "key1") {
            if (value.find("ull") != std::string::npos || value.find("ULL") != std::string::npos) {
                data.key1 = parseULL(value);
            }
            else {
                data.key1 = std::stoull(value);
            }
        }
        else if (key == "key2") {
            if (value.rfind("0b", 0) == 0 || value.rfind("0B", 0) == 0) {
                data.key2 = parseBinary(value);
            }
            else {
                data.key2 = std::stoull(value);
            }
        }
        else if (key == "key3") {
            if (value.front() == '"' && value.back() == '"') {
                data.key3 = value.substr(1, value.size() - 2);
            }
            else {
                is.setstate(std::ios::failbit);
                return is;
            }
        }
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    os << "(:key1 " << data.key1 << "ull :key2 " << data.key2
        << " :key3 \"" << data.key3 << "\")";
    return os;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1)
        return a.key1 < b.key1;
    if (a.key2 != b.key2)
        return a.key2 < b.key2;
    return a.key3.size() < b.key3.size();
}
#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>

namespace TahMed
{
    struct DataItem
    {
        unsigned long long key1;
        unsigned long long key2;
        std::string key3;
    };

    struct DelimiterIO
    {
        char del;
    };

    struct LITIO
    {
        unsigned long long& lit;
    };

    struct BINIO
    {
        unsigned long long& bin;
    };

    struct StringIO
    {
        std::string& str;
    };

    struct LabelIO
    {
        std::string lab;
    };

    std::istream& operator>>(std::istream& inStream, DelimiterIO&& delimiter);
    std::istream& operator>>(std::istream& inStream, LITIO&& literal);
    std::istream& operator>>(std::istream& inStream, BINIO&& binary);
    std::istream& operator>>(std::istream& inStream, StringIO&& stringData);
    std::istream& operator>>(std::istream& inStream, LabelIO&& labelData);
    std::istream& operator>>(std::istream& inStream, DataItem& input);
    std::ostream& operator<<(std::ostream& outStream, const DataItem& output);
    std::string toBinary(unsigned long long number);
}
#endif
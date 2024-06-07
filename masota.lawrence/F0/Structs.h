#ifndef STRUCTS_H
#define STRUCTS_H
#include <iostream>
#include <string>
#include <set>

namespace structs
{
    struct DelimiterIO
    {
        char del;
    };
    struct EnglishIO
    {
        std::string& eng;
    };
    struct RussianIO
    {
        std::set<std::string>& rus;
    };
    struct DictIO
    {
        std::pair<std::string, std::set<std::string>> dict_el;
    };
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, EnglishIO&& dest);
    std::istream& operator>>(std::istream& in, RussianIO&& dest);
    std::istream& operator>>(std::istream& in, DictIO& dest);
}
#endif

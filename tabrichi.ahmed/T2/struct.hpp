#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

namespace nspace
{
    struct Data
    {
        unsigned long long key1;
        unsigned long long key2;
        std::string key3;
    };

    struct DelimiterIO
    {
        char exp;
    };

    struct ULLBinIO
    {
        unsigned long long& ref;
    };

    struct StringIO
    {
        std::string& ref;
    };

    class iofmtguard
    {
    public:
        iofmtguard(std::basic_ios<char>& s);
        ~iofmtguard();
    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, ULLBinIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, Data& dest);
    std::ostream& operator<<(std::ostream& out, const Data& dest);
}

#endif
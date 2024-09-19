#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace namesp
{
    struct DataStruct
    {
        double key1 = 0.0;
        long long key2 = 0;
        std::string key3;
    };

    struct DelimiterIO
    {
        explicit DelimiterIO(char expected) : exp(expected) {}
        char exp;
    };

    struct DoubleIO
    {
        explicit DoubleIO(double& reference) : ref(reference) {}
        double& ref;
    };

    struct LITIO
    {
        explicit LITIO(long long& reference) : ref(reference) {}
        long long& ref;
    };

    struct StringIO
    {
        explicit StringIO(std::string& reference) : ref(reference) {}
        std::string& ref;
    };

    struct LabelIO
    {
        explicit LabelIO(const std::string& expected) : exp(expected) {}
        std::string exp;
    };

    class iofmtguard
    {
    public:
        explicit iofmtguard(std::basic_ios<char>& s);
        ~iofmtguard();
    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };

    std::string fromDoubleToScientific(double val);
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, DoubleIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, LabelIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::istream& operator>>(std::istream& in, LITIO&& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
    bool operator<(const DataStruct& first, const DataStruct& second);
}

#endif

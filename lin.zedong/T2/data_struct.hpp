#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <string>
#include <iostream>
namespace namesp
{
    struct DataStruct
    {
        double key1;
        long long key2;
        std::string key3;
    };
    struct DelimiterIO
    {
        char exp;
    };
    struct DoubleIO
    {
        double& ref;
    };
    struct LITIO
    {
        long long& ref;
    };
    struct StringIO
    {
        std::string& ref;
    };
    struct LabelIO
    {
        std::string exp;
    };
    struct Compare
    {
        bool operator()(DataStruct first, DataStruct second) const;
    };
    class iofmtguard
    {
    public:
        explicit iofmtguard(std::basic_ios< char >& s);
        ~iofmtguard();
    private:
        std::basic_ios< char >& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };
    std::string fromDoubleToScientific(double val);
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, DoubleIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, LabelIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::istream& operator>>(std::istream& in, LITIO&& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}
#endif

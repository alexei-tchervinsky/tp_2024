#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <string>

namespace mungoi 
{
    
    struct DataStruct 
    {
        double key1;
        long long key2;
        std::string key3;
    };

    struct DoubleIO 
    {
        double& d;
    };

    struct LongLongIO 
    {
        long long& ll;
    };

    struct StringIO 
    {
        std::string& str;
    };

    
    std::istream& operator>>(std::istream& in, DoubleIO&& dest);
    
    std::istream& operator>>(std::istream& in, LongLongIO&& dest);
    
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);
    
    bool operator<(const DataStruct& a, const DataStruct& b);

    
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
    
}

#endif // DATA_STRUCT_H


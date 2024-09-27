#ifndef FMT_HPP
#define FMT_HPP
#include <iostream>
namespace TAhm
{
    class Fmt
    {
    public:
        Fmt(std::basic_ios<char>& stream);
        ~Fmt();
    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize accuracy_;
        std::basic_ios<char>::fmtflags flags_;
    };
}
#endif
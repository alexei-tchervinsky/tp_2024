#ifndef FMTGUARD_HPP
#define FMTGUARD_HPP

#include <iostream>

namespace AliKn
{
    class Fmtguard
    {
    public:
        Fmtguard(std::basic_ios<char>& stream);
        ~Fmtguard();

    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize accuracy_;
        std::basic_ios<char>::fmtflags flags_;
    };
}
#endif

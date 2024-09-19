#ifndef FMTGUARD_HPP
#define FMTGUARD_HPP

#include <iostream>

namespace AliKN {

    class FmtGuard {
    public:
        FmtGuard(std::basic_ios<char>& stream);
        ~FmtGuard();

    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags flags_;
    };

}

#endif

#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <iostream>

namespace Data {
    class FormatGuard {
    public:
        explicit FormatGuard(std::basic_ios<char> &s);

        ~FormatGuard();

    private:
        std::basic_ios<char> &s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };
}

#endif

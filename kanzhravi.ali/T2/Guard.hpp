#ifndef GUARD_HPP
#define GUARD_HPP

#include <iostream>

namespace AliKN {
    class iofmtguard {
    public:
        iofmtguard(std::basic_ios<char>& stream);
        ~iofmtguard();

    private:
        std::basic_ios<char>& stream_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags flags_;
    };
}

#endif

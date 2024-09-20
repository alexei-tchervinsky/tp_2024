#ifndef GUARD_HPP
#define GUARD_HPP

#include <iostream>

namespace AliKN {

    class Guard {
    public:
        Guard(std::basic_ios<char>& stream);
        ~Guard();

    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags flags_;
    };

}

#endif

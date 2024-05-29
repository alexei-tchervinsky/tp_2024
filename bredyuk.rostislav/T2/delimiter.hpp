#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <string>

namespace bredyuk
{
    struct DelimiterIO
    {
        char exp;
    };

    struct DoubleIO
    {
        double& ref;
    };

    struct UnsignedLongLongIO
    {
        unsigned long long& ref;
    };

    struct StringIO
    {
        std::string& ref;
    };
}

#endif
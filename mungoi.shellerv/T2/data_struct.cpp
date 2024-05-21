#include "data_struct.h"
#include "guard.h"
#include <cmath>
#include <iostream>

namespace mungoi
{
    std::string fromDoubleToScientific(double val)
    {
        int exp = 0;
        if (val == 0 || std::abs(val) == 1)
            exp = 0;
        else if (std::abs(val) < 1)
        {
            while (std::abs(val) * 10 < 10)
            {
                val *= 10;
                exp--;
            }
        }
        else
        {
            while (std::abs(val) / 10 >= 1)
            {
                val /= 10;
                exp++;
            }
        }
        std::string res = std::to_string(val);
        if (res.find('0') == 2 && res[4] == '0')
        {
            res.erase(3);
        }
        else
        {
            res.erase(4);
        }
        std::string result = res + (exp < 0 ? "e-" : "e+") + std::to_string(std::abs(exp));
        return result;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(:key1 " << fromDoubleToScientific(src.key1);
        out << ":key2 " << src.key2 << "ll";
        out << ":key3 \"" << src.key3 << "\":)";
        return out;
    }
}

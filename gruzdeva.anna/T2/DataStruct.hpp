#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

// 15. key1: DBL LIT key2: ULL LIT
// input format (:keyX dataX:keyY dataY:keyZ dataZ)
#include <string>
#include <iostream>

namespace ds {
    struct DataStruct {
        double key1;
        unsigned long long key2;
        std::string key3;
    };

    struct DelimiterIO {
        char exp;
    };

    struct DoubleLitIO {
        double& value;
    };

    struct ULLLitIO {
        unsigned long long& value;
    };

    struct StringIO {
        std::string& value;
    };

    bool operator<(const DataStruct& rhs, const DataStruct& lhs);
    std::istream& operator>>(std::istream& is, DataStruct& ds);
    std::ostream& operator<<(std::ostream& os, const DataStruct& ds);

    std::istream& operator>>(std::istream& is, DelimiterIO&& d);
    std::istream& operator>>(std::istream& is, DoubleLitIO&& dl);
    std::istream& operator>>(std::istream& is, ULLLitIO&& ull);
    std::istream& operator>>(std::istream& is, StringIO&& str);
}

#endif //DATA_STRUCT_HPP
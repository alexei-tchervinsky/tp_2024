#include "DataStruct.h"
#include "FormatGuard.h"
#include <iostream>
#include <iomanip>

namespace Data {
    std::istream &operator>>(std::istream &in, DelimiterIO &&dest) {
        char c;
        return (in >> c && tolower(c) == dest.exp) ? in : (in.setstate(std::ios::failbit), in);
    }

    std::istream &operator>>(std::istream &in, DoubleIO &&dest) {
        return (in >> dest.ref && in >> DelimiterIO{'d'}) ? in : (in.setstate(std::ios::failbit), in);
    }

    std::istream &operator>>(std::istream &in, StringIO &&dest) {
        return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"') ? in : (in.setstate(std::ios::failbit), in);
    }

    std::istream &operator>>(std::istream &in, LitIO &&dest) {
        return (in >> dest.ref && in >> DelimiterIO{'l'} >> DelimiterIO{'l'}) ? in : (in.setstate(
                std::ios::failbit), in);
    }

    std::istream &operator>>(std::istream &in, LabelIO &&dest) {
        std::string data;
        return (in >> StringIO{data} && data == dest.exp) ? in : (in.setstate(std::ios::failbit), in);
    }

    std::istream &operator>>(std::istream &in, DataStruct &dest) {
        using namespace std::string_literals;

        std::string keyX;
        std::istream::sentry sentry(in);

        if (!(sentry && in >> DelimiterIO{'('})) return in;

        for (int i = 0; i < 3; ++i) {
            if (!(in >> DelimiterIO{':'} >> keyX)) return in;

            if (keyX == "key1") in >> DoubleIO{dest.key1};
            else if (keyX == "key2") in >> LitIO{dest.key2};
            else if (keyX == "key3") in >> StringIO{dest.key3};
            else return (in.setstate(std::ios::failbit), in);
        }

        return (in >> DelimiterIO{':'} >> DelimiterIO{')'}) ? in : (in.setstate(std::ios::failbit), in);
    }

    std::ostream &operator<<(std::ostream &out, const DataStruct &dest) {
        FormatGuard fmtGuard(out);
        return out << "(:key1 " << std::fixed << std::setprecision(1) << dest.key1 << "d"
                   << ":key2 " << dest.key2 << "ll"
                   << ":key3 \"" << dest.key3 << "\":)";
    }

    bool operator<(const DataStruct &first, const DataStruct &second) {
        if (first.key1 != second.key1) return first.key1 < second.key1;
        if (first.key2 != second.key2) return first.key2 < second.key2;
        return first.key3.size() < second.key3.size();
    }
}

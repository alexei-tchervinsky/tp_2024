#include "delimiter.hpp"

std::istream& lelkov::operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.expected)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

#include "inOutPut.h"

#include <iostream>
#include <bitset>
#include <string>

#include "delimiterIO.h"
#include "ullBinIO.h"
#include "ullLitIO.h"
#include "stringIO.h"
#include "delStrIO.h"
#include "dataStruct.h"
#include "iofmtguard.h"


std::istream& bylinskiy::operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    char c = '0';
    in >> c;
    if (in && (std::tolower(c) != std::tolower(dest.exp))) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& bylinskiy::operator>>(std::istream& in, UllLitIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    in >> dest.ref >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
    if (!in) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& bylinskiy::operator>>(std::istream& in, UllBinIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    in >> DelimiterIO{ '0' } >> DelimiterIO{ 'b' } >> dest.ref;
    if (!in) {
        in.setstate(std::ios::failbit);
    }
    dest.ref = std::bitset< sizeof(unsigned long long) * 8 >(dest.ref).to_ullong();
    return in;
}

std::istream& bylinskiy::operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& bylinskiy::operator>>(std::istream& in, DelStrIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    size_t i = 0;
    while (dest.exp[i] != '\0') {
        in >> DelimiterIO({ dest.exp[i++] });
    }
    return in;
}

std::istream& bylinskiy::operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    using del = DelimiterIO;
    using delStr = DelStrIO;
    using lit = UllLitIO;
    using bin = UllBinIO;
    using str = StringIO;

    DataStruct input;

    in >> delStr({ "(:" });
    int number = 0;

    for (size_t i = 0; i < 3; i++) {
        in >> delStr({ "key" }) >> number;
        if (number == 1) {
            in >> lit{ input.key1 };
        }
        else if (number == 2) {
            in >> bin{ input.key2 };
        }
        else if (number == 3) {
            in >> str{ input.key3 };
        }
        else {
            in.setstate(std::ios::failbit);
        }

        in >> del{ ':' };
    }

    in >> del{ ')' };

    if (in) {
        dest = input;
    }
    return in;
}

std::ostream& bylinskiy::operator<<(std::ostream& out, const DataStruct& src)
{
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }
    iofmtguard fmtguard(out);

    out << "(:key1 " << src.key1 << "ull";

    std::string bin = std::bitset< sizeof(unsigned long long) * 8 >(src.key2).to_string();
    long unsigned int pos = 0;
    while (bin[pos] == '0' && pos < bin.length() - 1) {
        pos++;
    }

    bin = bin.substr(pos);
    if (bin[0] != '0') {
        bin = "0" + bin;
    }

    out << ":key2 0b" << bin;
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
}

bylinskiy::iofmtguard::iofmtguard(std::basic_ios< char >& s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
{
}

bylinskiy::iofmtguard::~iofmtguard()
{
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}

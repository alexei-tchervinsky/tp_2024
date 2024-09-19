#include "FmtGuard.hpp"

namespace AliKN {

    FmtGuard::FmtGuard(std::basic_ios<char>& stream)
        : s_(stream), fill_(stream.fill()), precision_(stream.precision()), flags_(stream.flags()) {}

    FmtGuard::~FmtGuard() {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(flags_);
    }
}

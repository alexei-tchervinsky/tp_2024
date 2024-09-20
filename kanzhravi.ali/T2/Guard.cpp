#include "Guard.hpp"

namespace AliKN {

    Guard::Guard(std::basic_ios<char>& stream)
        : s_(stream), fill_(stream.fill()), precision_(stream.precision()), flags_(stream.flags()) {}

    Guard::~Guard() {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(flags_);
    }
}

#include "Fmtguard.hpp"

namespace TahMed
{
    Fmtguard::Fmtguard(std::basic_ios<char>& stream)
        : s_(stream), fill_(stream.fill()), accuracy_(stream.precision()), flags_(stream.flags()) {}

    Fmtguard::~Fmtguard()
    {
        s_.fill(fill_);
        s_.precision(accuracy_);
        s_.flags(flags_);
    }
}
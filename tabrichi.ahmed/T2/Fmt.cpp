#include "Fmt.hpp"
namespace TAhm
{
    Fmt::Fmt(std::basic_ios<char>& stream)
        : s_(stream), fill_(stream.fill()), accuracy_(stream.precision()), flags_(stream.flags()) {}
    Fmt::~Fmt()
    {
        s_.fill(fill_);
        s_.precision(accuracy_);
        s_.flags(flags_);
    }
}
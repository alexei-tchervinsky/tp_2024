#include "Delimiter.h"

namespace lawrenced {
    
    std::istream& operator>>(std::istream& in, const Delimiter& exp) {
        char current_char;
        if (in >> current_char && current_char != exp.expected) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    
    std::istream& operator>>(std::istream& in, const StringDelimiter& exp) {
        const char* p = exp.expected;
        char ch;
        while (*p != '\0' && in >> ch && ch == *p) {
            ++p;
        }
        if (*p != '\0') {
            in.setstate(std::ios::failbit);
        }
        
        return in;
    }

} // namespace jean


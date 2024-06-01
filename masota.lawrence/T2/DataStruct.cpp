#include "DataStruct.h"
#include <limits>
#include <iostream>  // For debugging purposes

namespace jean {

  std::istream& operator>>(std::istream& in, DataStruct& ds) {
    char ch;
    // Check for the initial '('
    if (!(in >> ch && ch == '(')) {
      std::cerr << "Parsing failed: expected '(', found '" << ch << "'\n";  // Debugging message
      return in;
    }

    // Consume until 'key1' (safe-guard against unexpected characters before key1)
    in.ignore(std::numeric_limits<std::streamsize>::max(), 'k');
    in.ignore(std::numeric_limits<std::streamsize>::max(), 'e');
    in.ignore(std::numeric_limits<std::streamsize>::max(), 'y');
    in.ignore(std::numeric_limits<std::streamsize>::max(), '1');
    in.ignore(std::numeric_limits<std::streamsize>::max(), ' ');

    // Parse key1
    if (!(in >> ds.key1)) {
      std::cerr << "Parsing failed at key1\n";  // Debugging message
      return in;
    }

    // Skip to key2 similarly
    in.ignore(std::numeric_limits<std::streamsize>::max(), 'k');
    in.ignore(std::numeric_limits<std::streamsize>::max(), 'e');
    in.ignore(std::numeric_limits<std::streamsize>::max(), 'y');
    in.ignore(std::numeric_limits<std::streamsize>::max(), '2');
    in.ignore(std::numeric_limits<std::streamsize>::max(), ' ');

    // Parse key2
    if (!(in >> ds.key2)) {
      std::cerr << "Parsing failed at key2\n";  // Debugging message
      return in;
    }

    // Skip to key3 similarly
    in.ignore(std::numeric_limits<std::streamsize>::max(), 'k');
    in.ignore(std::numeric_limits<std::streamsize>::max(), 'e');
    in.ignore(std::numeric_limits<std::streamsize>::max(), 'y');
    in.ignore(std::numeric_limits<std::streamsize>::max(), '3');
    in.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    in.ignore(std::numeric_limits<std::streamsize>::max(), '"');

    // Parse key3
    std::getline(in, ds.key3, '"');  // Read the string content until the closing quote

    // Expect the closing part
    if (!(in >> std::ws >> ch && ch == ':')) {
      std::cerr << "Parsing failed at closing ':)'\n";  // Debugging message
      return in;
    }
    if (!(in >> ch && ch == ')')) {
      std::cerr << "Parsing failed at closing ')'\n";  // Debugging message
      return in;
    }

    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& ds) {
    out << "(:key1 " << ds.key1 << ":key2 " << ds.key2 << ":key3 \"" << ds.key3 << "\":)";
    return out;
  }

} // namespace jean


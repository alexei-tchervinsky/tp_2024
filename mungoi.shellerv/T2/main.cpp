#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

struct DataStruct {
    double key1;
    long long key2;
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    std::string input;
    if (!std::getline(in, input, ')')) {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::istringstream iss(input + ')');
    char c;
    if (!(iss >> c) || c != '(') {
        in.setstate(std::ios::failbit);
        return in;
    }

    bool key1_set = false, key2_set = false, key3_set = false;
    while (iss >> c) {
        if (c == ':') {
            std::string key;
            if (!(iss >> key)) {
                in.setstate(std::ios::failbit);
                return in;
            }

            if (key == "key1") {
                if (!(iss >> data.key1) || !(iss >> c) || (c != 'd' && c != 'D')) {
                    in.setstate(std::ios::failbit);
                    return in;
                }
                key1_set = true;
            } else if (key == "key2") {
                if (!(iss >> data.key2) || !(iss >> c) || (c != 'l' && c != 'L') || !(iss >> c) || (c != 'l' && c != 'L')) {
                    in.setstate(std::ios::failbit);
                    return in;
                }
                key2_set = true;
            } else if (key == "key3") {
                if (!(iss >> std::quoted(data.key3))) {
                    in.setstate(std::ios::failbit);
                    return in;
                }
                key3_set = true;
            } else {
                in.setstate(std::ios::failbit);
                return in;
            }
        }

        if (iss.peek() == ')') {
            break;
        }
    }

    if (!(key1_set && key2_set && key3_set)) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    std::ostream::sentry sentry(out);
    if (!sentry) return out;

    out << "( :key1 " << std::fixed << std::setprecision(1) << data.key1
        << "d :key2 " << data.key2 << "ll :key3 " << std::quoted(data.key3) << " )";
    return out;
}

int main() {
    std::vector<DataStruct> data;
    std::istringstream iss(
        "( :key1 45.0d :key2 123ll :key3 \"Apple\" )\n"
        "( :key1 10.5d :key2 -45ll :key3 \"Banana\" )\n"
        "( :key1 45.0d :key2 123ll :key3 \"Cherry\" )\n"
        "( :key1 10.5d :key2 123ll :key3 \"Date\" )\n"
        "( :key1 45.0d :key2 -123ll :key3 \"Fig\" )\n"
    );

    try {
        std::copy(
            std::istream_iterator<DataStruct>(iss),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );

        if (data.empty()) {
            std::cerr << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
            return 1;
        }

        std::sort(data.begin(), data.end(), [](const DataStruct& a, const DataStruct& b) {
            if (a.key1 != b.key1)
                return a.key1 < b.key1;
            if (a.key2 != b.key2)
                return a.key2 < b.key2;
            return a.key3 < b.key3;
        });

        std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 2;
    }

    return 0;
}

#include "data_struct.h"
#include <sstream>
#include <iomanip>

std::istream& operator>>(std::istream& is, DataStruct& ds) {
    std::string line;
    if (std::getline(is, line)) {
        std::istringstream iss(line);
        char colon, bracket, type;
        if (iss >> bracket >> colon && bracket == '(' && colon == ':') {
            std::string key;
            while (iss >> key) {
                if (key == "key1") {
                    iss >> ds.key1 >> type >> colon;
                }
                else if (key == "key2") {
                    iss >> ds.key2 >> type >> colon;
                }
                else if (key == "key3") {
                    iss >> std::quoted(ds.key3) >> colon;
                }
                if (colon != ':') break;
            }
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
    return os << "(:key1 " << ds.key1 << "d:key2 " << ds.key2 << "ll:key3 \"" << ds.key3 << "\":)";
}

bool operator<(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3 < b.key3;
}

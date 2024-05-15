#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iomanip>

struct DataStruct {
    double key1;
    long long key2;
    std::string key3;
};

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

int main() {
    std::vector<DataStruct> data;

    std::string testData = R"(
    (:key1 45.0d:key2 123ll:key3 "Apple":)
    (:key1 10.5d:key2 -45ll:key3 "Banana":)
    (:key1 45.0d:key2 123ll:key3 "Cherry":)
    (:key1 10.5d:key2 123ll:key3 "Date":)
    (:key1 45.0d:key2 -123ll:key3 "Fig":)
    )";

    std::istringstream iss(testData);

    std::copy(std::istream_iterator<DataStruct>(iss),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data));

    std::sort(data.begin(), data.end());

    std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}

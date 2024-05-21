#include "data_struct.h"
#include <sstream>
#include <iomanip>
#include <regex>

// Updated parsing logic for operator>>
std::istream& operator>>(std::istream& in, DataStruct& data)
{
    std::istream::sentry sentry(in);
    if (!sentry)
        return in;

    std::string input;
    if (!std::getline(in, input, ')'))
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::istringstream iss(input + ')');
    char c;
    if (!(iss >> c) || c != '(')
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    bool key1_set = false, key2_set = false, key3_set = false;
    std::string key;
    double key1_temp;
    long long key2_temp;
    std::string key3_temp;

    std::regex key1_pattern(R"(:key1\s*(-?\d+(\.\d*)?([eE][+-]?\d+)?d))");
    std::regex key2_pattern(R"(:key2\s*(-?\d+ll))");
    std::regex key3_pattern(R"(:key3\s*"(.*)");

    std::smatch match;
    if (std::regex_search(input, match, key1_pattern) && match.size() > 1)
    {
        key1_temp = std::stod(match.str(1));
        key1_set = true;
    }
    if (std::regex_search(input, match, key2_pattern) && match.size() > 1)
    {
        key2_temp = std::stoll(match.str(1));
        key2_set = true;
    }
    if (std::regex_search(input, match, key3_pattern) && match.size() > 1)
    {
        key3_temp = match.str(1);
        key3_set = true;
    }

    if (key1_set && key2_set && key3_set)
    {
        data.key1 = key1_temp;
        data.key2 = key2_temp;
        data.key3 = key3_temp;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }

    return in;
}

// Unchanged output operator
std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
        return out;

    out << "( :key1 " << std::fixed << std::setprecision(1) << data.key1 <<
        "d :key2 " << data.key2 << "ll :key3 " << std::quoted(data.key3) << " )";
    return out;
}
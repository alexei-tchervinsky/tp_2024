#include "data_struct.h"
#include <sstream>
#include <iomanip>
#include <iostream>

std::istream& operator>>(std::istream& in, DataStruct& data)
{
    std::istream::sentry sentry(in);
    if (!sentry)
        return in;

    std::string input;
    if (!std::getline(in, input, ')'))
    {
        std::cerr << "Error reading line" << std::endl;
        in.setstate(std::ios::failbit);
        return in;
    }

    std::istringstream iss(input + ')');
    char c;
    if (!(iss >> c) || c != '(')
    {
        std::cerr << "Expected '(', but got: " << c << std::endl;
        in.setstate(std::ios::failbit);
        return in;
    }

    bool key1_set = false, key2_set = false, key3_set = false;

    while (iss >> c)
    {
        if (c == ':')
        {
            std::string key;
            if (!(iss >> key))
            {
                std::cerr << "Error reading key" << std::endl;
                in.setstate(std::ios::failbit);
                return in;
            }

            if (key == "key1")
            {
                if (!(iss >> data.key1) || !(iss >> c) || c != 'd')
                {
                    std::cerr << "Error reading key1" << std::endl;
                    in.setstate(std::ios::failbit);
                    return in;
                }
                key1_set = true;
            }
            else if (key == "key2")
            {
                if (!(iss >> data.key2) || !(iss >> c) || c != 'l' || !(iss >> c) || c != 'l')
                {
                    std::cerr << "Error reading key2" << std::endl;
                    in.setstate(std::ios::failbit);
                    return in;
                }
                key2_set = true;
            }
            else if (key == "key3")
            {
                if (!(iss >> std::quoted(data.key3)))
                {
                    std::cerr << "Error reading key3" << std::endl;
                    in.setstate(std::ios::failbit);
                    return in;
                }
                key3_set = true;
            }
            else
            {
                std::cerr << "Unknown key: " << key << std::endl;
                in.setstate(std::ios::failbit);
                return in;
            }
        }

        if (iss.peek() == ')')
            break;
    }

    if (!(key1_set && key2_set && key3_set))
    {
        std::cerr << "Missing keys in input" << std::endl;
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
        return out;

    out << "( :key1 " << std::fixed << std::setprecision(1) << data.key1 <<
        "d :key2 " << data.key2 << "ll :key3 " << std::quoted(data.key3) << " )";
    return out;
}
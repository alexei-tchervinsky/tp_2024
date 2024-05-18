#include "data_struct.h"
#include <sstream>
#include <iomanip>
#include <iostream>  // Include for debugging

std::istream& operator>>(std::istream& in, DataStruct& data)
{
    std::istream::sentry sentry(in);
    if (!sentry)
        return in;

    std::string input;
    if (!std::getline(in, input, ')'))
    {
        std::cerr << "Error reading line" << std::endl;  // Debugging output
        in.setstate(std::ios::failbit);
        return in;
    }

    std::istringstream iss(input + ')');
    char c;
    if (!(iss >> c) || c != '(')
    {
        std::cerr << "Expected '(', but got: " << c << std::endl;  // Debugging output
        in.setstate(std::ios::failbit);
        return in;
    }

    while (iss >> c)
    {
        if (c == ':')
        {
            std::string key;
            if (!(iss >> key))
            {
                std::cerr << "Error reading key" << std::endl;  // Debugging output
                in.setstate(std::ios::failbit);
                return in;
            }

            if (key == "key1")
            {
                if (!(iss >> data.key1) || !(iss >> c) || (c != 'd' && c != 'D'))
                {
                    std::cerr << "Error reading key1" << std::endl;  // Debugging output
                    in.setstate(std::ios::failbit);
                    return in;
                }
            }
            else if (key == "key2")
            {
                if (!(iss >> data.key2) || !(iss >> c) || (c != 'l' &&
                    c != 'L') || !(iss >> c) || (c != 'l' && c != 'L'))
                {
                    std::cerr << "Error reading key2" << std::endl;  // Debugging output
                    in.setstate(std::ios::failbit);
                    return in;
                }
            }
            else if (key == "key3")
            {
                if (!(iss >> std::quoted(data.key3)))
                {
                    std::cerr << "Error reading key3" << std::endl;  // Debugging output
                    in.setstate(std::ios::failbit);
                    return in;
                }
            }
            else
            {
                std::cerr << "Unknown key: " << key << std::endl;  // Debugging output
                in.setstate(std::ios::failbit);
                return in;
            }
        }

        if (iss.peek() == ')')
            break;
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

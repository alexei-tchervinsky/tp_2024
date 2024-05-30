#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <functional>
#include "commands.hpp"

int main()
{
    std::unordered_map<char, std::string> huff;
    std::unordered_map <std::string,
        std::function<void(bredyuk::huffCode, std::istream&, std::ostream&)>> cmd;
    cmd["HELP"] = std::bind(bredyuk::help, std::placeholders::_3);
    cmd["CREATE"] = std::bind(bredyuk::create, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cmd["DISPLAY"] = std::bind(bredyuk::display, std::placeholders::_1, std::placeholders::_3);

    std::string command = "";
    while (std::cin >> command)
    {
        try
        {
            cmd.at(command)(huff, std::cin, std::cout);
        }
        catch (const std::exception&)
        {
            std::cout << "<INVALID COMMAND>" << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

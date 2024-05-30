#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <functional>
#include "commands.hpp"
using namespace bredyuk;

int main()
{
    std::unordered_map<char, std::string> huff;
    std::unordered_map <std::string,
        std::function<void(bredyuk::huffCode&, std::istream&, std::ostream&)>> cmd;
    std::cout << "To make Huffman tree, type CREATE\n";
    std::cout << "To show Huffman codes, type DISPLAY\n";
    cmd["CREATE"] = bredyuk::create;
    cmd["DISPLAY"] = bredyuk::display;

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

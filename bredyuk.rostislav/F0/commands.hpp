#ifndef COMMANDS_HPP
#define COMMAND_HPP
#include <iostream>
#include <unordered_map>

namespace bredyuk
{
    struct Node
    {
        char ch;
        int freq = 0;
        Node* left;
        Node* right = nullptr;
    };
    using huffCode = std::unordered_map<char, std::string>;



    void create(huffCode huffmanCode, std::istream& in, std::ostream& out);
    void display(huffCode& huffmanCode, std::istream& in, std::ostream& out);
    void encode(huffCode& huffmanCode, bredyuk::Node* root, std::string str);
}

#endif

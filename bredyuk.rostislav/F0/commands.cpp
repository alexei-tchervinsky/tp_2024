#include "commands.hpp"
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <exception>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>


// Function to allocate a new tree node
bredyuk::Node* getNode(char ch, int freq, bredyuk::Node* left, bredyuk::Node* right)
{
    bredyuk::Node* node = new bredyuk::Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}
// compare object to be used to order the heap
struct compare
{
    bool operator()(bredyuk::Node* l, bredyuk::Node* r)
    {
        // highest priority item has lowest frequency
        return l->freq > r->freq;
    }
};
void bredyuk::display(huffCode& huffmanCode, std::istream& in, std::ostream& out) {
    for (auto pair : huffmanCode) {
        out << pair.first << " " << pair.second << '\n';
    }
}
void bredyuk::create(huffCode huffmanCode, std::istream& in, std::ostream& out)
{
    std::unordered_map<char, int> freq;
    std::priority_queue<bredyuk::Node*, std::vector<bredyuk::Node*>, compare> prior_que;
    std::string name = "";
    out << "Type in name of file from where to read text";
    in >> name;
    if (!in)
    {
        throw std::runtime_error("<INVALID COMMAND>");
    }
    std::string str = "";
    std::ifstream inp(name);
    if (!inp.is_open())
    {
        throw std::runtime_error("<THERE`S NO SUCH FILE>");
    }
    std::string text;
    while (!inp.eof())
    {
        std::string temp;
        std::getline(inp, temp);
        if (!inp.eof())
        {
            temp += '\n';
        }
        text += temp;
    }
    inp.close();
    if (text.size() == 1) {
        out << "Code for your single symbol: " << *text.begin() << " is 0";
        return;
    }
    for (char ch : text) {
        freq[ch]++;
    }
    for (auto pair : freq) {
        prior_que.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }
    while (prior_que.size() != 1)
    {
        bredyuk::Node* left = prior_que.top();
        prior_que.pop();
        bredyuk::Node* right = prior_que.top();
        prior_que.pop();
        int sum = left->freq + right->freq;
        prior_que.push(getNode('\0', sum, left, right));
    }
    bredyuk::Node* root = prior_que.top();
    bredyuk::encode(huffmanCode, root, "");
    std::string encode_str = "";
    for (char ch : text) {
        encode_str += huffmanCode[ch];
    }

    out << "Type in name of file to where you want to send encoded text";
    in >> name;
    if (!in)
    {
        throw std::runtime_error("<INVALID COMMAND>");
    }
    std::ofstream outp(name);
    outp << encode_str;
    outp.close();
}
void bredyuk::encode(huffCode& huffmanCode, bredyuk::Node* root, std::string str)
{
    if (root == nullptr)
        return;

    // found a leaf node
    if (!root->left && !root->right) {
        (huffmanCode)[root->ch] = str;
    }

    bredyuk::encode(huffmanCode, root->left, str + "0");
    bredyuk::encode(huffmanCode, root->right, str + "1");
}

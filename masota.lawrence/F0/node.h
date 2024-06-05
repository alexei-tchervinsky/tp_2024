#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

// Node structure representing a node in the 2-3 tree
struct Node {
    std::vector<std::string> keys;                    // List of keys (English words)
    std::vector<std::vector<std::string>> translations; // Translations for each key
    std::vector<Node*> children;                      // Pointers to child nodes

    // Constructor to initialize the children to nullptr
    Node() { children.resize(3, nullptr); }

    // Check if the node is a leaf (has no children)
    bool isLeaf() const { return children[0] == nullptr; }
};

#endif


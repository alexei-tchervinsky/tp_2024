#ifndef TWO_THREE_TREE_H
#define TWO_THREE_TREE_H

#include "node.h"
#include <vector>
#include <string>

class TwoThreeTree {
public:
    TwoThreeTree();                                // Constructor
    ~TwoThreeTree();                               // Destructor

    void insert(const std::string& key, const std::vector<std::string>& translations);
    bool search(const std::string& key) const;
    void deleteKey(const std::string& key);
    void printTree() const;

private:
    Node* root;                                    // Pointer to the root node

    // Internal utility functions
    Node* insertInternal(Node* node, const std::string& key, const std::vector<std::string>& translations, Node*& newChild);
    Node* searchInternal(Node* node, const std::string& key) const;
    Node* split(Node* node);
    Node* deleteRecursive(Node* node, const std::string& key);
    void fixUnderflow(Node* parent, int pos);
    void clear(Node* node);
    void printNode(const Node* node, int depth) const;
};

#endif

//std::map for dicy to include it

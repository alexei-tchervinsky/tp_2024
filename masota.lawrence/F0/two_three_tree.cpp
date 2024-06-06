// two_three_tree.cpp
#include "two_three_tree.h"
#include <iostream>
#include <algorithm>

TwoThreeTree::TwoThreeTree() : root(nullptr) {}

TwoThreeTree::~TwoThreeTree() {
    clear(root);
}

// Recursive function to free all nodes
void TwoThreeTree::clear(Node* node) {
    if (node) {
        for (auto child : node->children)
            clear(child);
        delete node;
    }
}

// Public function to insert a key with translations
void TwoThreeTree::insert(const std::string& key, const std::vector<std::string>& translations) {
    if (!root) {
        root = new Node();
        root->keys.push_back(key);
        root->translations.push_back(translations);
    }
    else {
        Node* node = root;
        Node* parent = nullptr;

        while (!node->isLeaf()) {
            parent = node;
            int pos = 0;
            while (pos < static_cast<int>(node->keys.size()) && key > node->keys[pos]) pos++;
            node = node->children[pos];
        }

        node->keys.push_back(key);
        node->translations.push_back(translations);
        std::sort(node->keys.begin(), node->keys.end());  // Ensure the keys are sorted

        // Handle overflow
        if (node->keys.size() > 2) {
            // Split the node
            Node* newNode = new Node();
            //removed smtng
            newNode->keys.push_back(node->keys[2]);
            newNode->translations.push_back(node->translations[2]);
            node->keys.resize(2);
            node->translations.resize(2);

            if (!parent) {
                // Create new root if there was no parent (i.e., splitting the root)
                root = new Node();
                root->keys.push_back(node->keys[1]);
                root->translations.push_back(node->translations[1]);
                root->children = { node, newNode };
            }
            else {
                // Insert the middle key into the parent node
                int parentPos = 0;
                while (parentPos < static_cast<int>(parent->keys.size()) && node->keys[1] > parent->keys[parentPos]) parentPos++;
                parent->keys.insert(parent->keys.begin() + parentPos, node->keys[1]);
                parent->translations.insert(parent->translations.begin() + parentPos, node->translations[1]);
                parent->children.insert(parent->children.begin() + parentPos + 1, newNode);
            }
        }
    }
}

// Recursive function to insert a key into the correct location in the 2-3 tree
Node* TwoThreeTree::insertInternal(Node* node, const std::string& key, const std::vector<std::string>& translations, Node*& newChild) {
    if (node == nullptr) {
        // Base case: create a new leaf node if the tree is empty
        newChild = new Node();
        newChild->keys.push_back(key);
        newChild->translations.push_back(translations);
        return nullptr;
    }

    int pos = 0;
    while (pos < static_cast<int>(node->keys.size()) && key > node->keys[pos]) pos++;

    if (node->isLeaf()) {
        // Insert the new key and translations into the current leaf node
        node->keys.insert(node->keys.begin() + pos, key);
        node->translations.insert(node->translations.begin() + pos, translations);
        if (node->keys.size() > 2) {
            // If the node overflows, split it
            return split(node);
        }
        return nullptr;
    }

    // Recursive case: insert into the appropriate child
    Node* child = insertInternal(node->children[pos], key, translations, newChild);
    if (child) {
        node->keys.insert(node->keys.begin() + pos, child->keys[0]);
        node->translations.insert(node->translations.begin() + pos, child->translations[0]);
        node->children.insert(node->children.begin() + pos + 1, child);

        if (node->keys.size() > 2) {
            // If the node overflows, split it
            return split(node);
        }
    }

    return nullptr;
}

// Splits a full node and returns the newly created child node
Node* TwoThreeTree::split(Node* node) {
    Node* newChild = new Node();

    // The middle index to use for splitting
    int midIndex = 1;

    // Copy the keys and translations to the new node
    newChild->keys.push_back(node->keys[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(midIndex) + 1]);
    newChild->translations.push_back(node->translations[static_cast<std::vector<std::vector<std::string, std::allocator<std::string>>, std::allocator<std::vector<std::string, std::allocator<std::string>>>>::size_type>(midIndex) + 1]);

    // If the node isn't a leaf, adjust the children pointers
    if (!node->isLeaf()) {
        newChild->children = { node->children[midIndex + 1], node->children[midIndex + 2] };
    }

    // Adjust the original node's keys and translations
    node->keys.resize(midIndex);
    node->translations.resize(midIndex);
    node->children.resize(static_cast<std::vector<Node*, std::allocator<Node*>>::size_type>(midIndex) + 1);

    return newChild;
}

//Revised search method
bool TwoThreeTree::search(const std::string& key) const {
    return searchInternal(root, key);
}


//Revised search internal
Node* TwoThreeTree::searchInternal(Node* node, const std::string& key) const {
    if (!node) return nullptr;  // Base case: key not found

    // Iterate over keys in the current node
    for (int i = 0; i < static_cast<int>(node->keys.size()); i++) {
        if (key == node->keys[i]) {
            return node;  // Key found in the current node
        }
        else if (key < node->keys[i]) {
            // Key is less than the current key, search in the left child
            return searchInternal(node->children[i], key);
        }
    }

    // If key is greater than all keys in the current node, search in the rightmost child
    return searchInternal(node->children[node->keys.size()], key);
}



// Public function to delete a key
void TwoThreeTree::deleteKey(const std::string& key) {
    root = deleteRecursive(root, key);
}


// Recursive function to delete a key
Node* TwoThreeTree::deleteRecursive(Node* node, const std::string& key) {
    if (!node) return nullptr;

    int pos = 0;
    while (pos < static_cast<int>(node->keys.size()) && node->keys[pos] < key) ++pos;

    // If found in the current node and it's a leaf, delete it directly
    if (node->isLeaf() && pos < static_cast<int>(node->keys.size()) && node->keys[pos] == key) {
        node->keys.erase(node->keys.begin() + pos);
        node->translations.erase(node->translations.begin() + pos);
        if (node->keys.empty()) {
            delete node;
            return nullptr;
        }
        return node;
    }

    // If not found and it's a leaf, nothing to do
    if (node->isLeaf()) return node;

    // Recurse into the appropriate child node
    Node* child = deleteRecursive(node->children[pos], key);
    if (!child) node->children.erase(node->children.begin() + pos);

    // Handle underflow if any
    if (node->children[pos]->keys.size() < 1) {
        fixUnderflow(node, pos);
    }

    return node;
}


// Correct underflow by borrowing or merging nodes
void TwoThreeTree::fixUnderflow(Node* parent, int pos) {
    Node* child = parent->children[pos];

    // Try to borrow from the left sibling
    if (pos > 0 && parent->children[static_cast<std::vector<Node*, std::allocator<Node*>>::size_type>(pos) - 1]->keys.size() > 1) {
        Node* leftSibling = parent->children[static_cast<std::vector<Node*, std::allocator<Node*>>::size_type>(pos) - 1];
        child->keys.insert(child->keys.begin(), leftSibling->keys.back());
        child->translations.insert(child->translations.begin(), leftSibling->translations.back());
        leftSibling->keys.pop_back();
        leftSibling->translations.pop_back();
        return;
    }

    // Try to borrow from the right sibling
    if (pos < static_cast<int>(parent->children.size()) - 1 && parent->children[static_cast<std::vector<Node*, std::allocator<Node*>>::size_type>(pos) + 1]->keys.size() > 1) {
        Node* rightSibling = parent->children[static_cast<std::vector<Node*, std::allocator<Node*>>::size_type>(pos) + 1];
        child->keys.push_back(rightSibling->keys.front());
        child->translations.push_back(rightSibling->translations.front());
        rightSibling->keys.erase(rightSibling->keys.begin());
        rightSibling->translations.erase(rightSibling->translations.begin());
        return;
    }

    // Merge with a sibling if borrowing is not possible
    if (pos > 0) {
        // Merge with left sibling
        Node* leftSibling = parent->children[static_cast<std::vector<Node*, std::allocator<Node*>>::size_type>(pos) - 1];
        leftSibling->keys.insert(leftSibling->keys.end(), child->keys.begin(), child->keys.end());
        leftSibling->translations.insert(leftSibling->translations.end(), child->translations.begin(), child->translations.end());
        delete child;
        parent->children.erase(parent->children.begin() + pos);
    }
    else {
        // Merge with right sibling
        Node* rightSibling = parent->children[static_cast<std::vector<Node*, std::allocator<Node*>>::size_type>(pos) + 1];
        child->keys.insert(child->keys.end(), rightSibling->keys.begin(), rightSibling->keys.end());
        child->translations.insert(child->translations.end(), rightSibling->translations.begin(), rightSibling->translations.end());
        delete rightSibling;
        parent->children.erase(parent->children.begin() + pos + 1);
    }
}

// Print the entire tree structure
void TwoThreeTree::printTree() const {
    printNode(root, 0);
}

// Helper function to join vector of strings with a delimiter
std::string join(const std::vector<std::string>& vec, const std::string& delim) {
    std::string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        result += vec[i];
        if (i < vec.size() - 1) result += delim;
    }
    return result;
}



// revised printNode
void TwoThreeTree::printNode(const Node* node, int depth) const {
    if (!node) return;

    // Print spaces for current depth to visualize tree structure
    std::string indent(depth * 4, ' ');  // Indent nodes based on tree depth
    std::cout << indent;

    // Check if the node is a leaf or internal
    if (node->isLeaf()) {
        std::cout << "Leaf: ";
    }
    else {
        std::cout << "Internal: ";
    }

    // Print each key and its translations in the node
    std::cout << "[";
    for (size_t i = 0; i < node->keys.size(); ++i) {
        std::cout << node->keys[i] << " (";
        // Print all translations for the current key
        for (size_t j = 0; j < node->translations[i].size(); ++j) {
            std::cout << node->translations[i][j];
            if (j < node->translations[i].size() - 1) std::cout << ", ";
        }
        std::cout << ")";
        if (i < node->keys.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    // Recursively print child nodes
    for (Node* child : node->children) {
        if (child != nullptr) printNode(child, depth + 1);
    }
}


#include "struct.h"
#include <algorithm>
#include <iostream>

AVLNode::AVLNode(const std::string& word, const std::string& translation)
    : key(word), balanceFactor(0) {
    translations.push_back(translation);
}

AVLTree::AVLTree() : root(nullptr) {}

void AVLTree::insert(const std::string& word, const std::string& translation) {
    insert(root, word, translation);
}

void AVLTree::remove(const std::string& word) {
    remove(root, word);
}

void AVLTree::rotateLeft(std::unique_ptr<AVLNode>& node) {
    auto temp = std::move(node->right);
    node->right = std::move(temp->left);
    temp->left = std::move(node);
    node = std::move(temp);
}

void AVLTree::rotateRight(std::unique_ptr<AVLNode>& node) {
    auto temp = std::move(node->left);
    node->left = std::move(temp->right);
    temp->right = std::move(node);
    node = std::move(temp);
}

void AVLTree::balanceTree(std::unique_ptr<AVLNode>& node) {
    updateBalanceFactor(node);
    if (node->balanceFactor == -2) {
        if (node->left->balanceFactor <= 0) {
            rotateRight(node);
        }
        else {
            rotateLeft(node->left);
            rotateRight(node);
        }
    }
    else if (node->balanceFactor == 2) {
        if (node->right->balanceFactor >= 0) {
            rotateLeft(node);
        }
        else {
            rotateRight(node->right);
            rotateLeft(node);
        }
    }
}

void AVLTree::insert(std::unique_ptr<AVLNode>& node, const std::string& word, const std::string& translation) {
    if (!node) {
        node = std::make_unique<AVLNode>(word, translation);
    }
    else if (word < node->key) {
        insert(node->left, word, translation);
    }
    else if (word > node->key) {
        insert(node->right, word, translation);
    }
    else {
        node->translations.push_back(translation);
    }
    balanceTree(node);
}

void AVLTree::remove(std::unique_ptr<AVLNode>& node, const std::string& word) {
    if (!node) return;

    if (word < node->key) {
        remove(node->left, word);
    }
    else if (word > node->key) {
        remove(node->right, word);
    }
    else {
        if (!node->left && !node->right) {
            node.reset();
        }
        else if (!node->left) {
            node = std::move(node->right);
        }
        else if (!node->right) {
            node = std::move(node->left);
        }
        else {
            AVLNode* temp = findMin(node->right.get());
            node->key = temp->key;
            node->translations = temp->translations;
            remove(node->right, temp->key);
        }
    }

    if (node) {
        balanceTree(node);
    }
}

AVLNode* AVLTree::findMin(AVLNode* node) {
    while (node->left) {
        node = node->left.get();
    }
    return node;
}

int AVLTree::height(const std::unique_ptr<AVLNode>& node) {
    if (!node) return -1;
    return 1 + std::max(height(node->left), height(node->right));
}

void AVLTree::updateBalanceFactor(std::unique_ptr<AVLNode>& node) {
    node->balanceFactor = height(node->right) - height(node->left);
}

std::vector<std::string> AVLTree::search(const std::string& word) {
    AVLNode* current = root.get();
    while (current) {
        if (word == current->key) {
            return current->translations;
        }
        else if (word < current->key) {
            current = current->left.get();
        }
        else {
            current = current->right.get();
        }
    }
    return {};
}

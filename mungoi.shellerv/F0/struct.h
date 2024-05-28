#ifndef STRUCT_H
#define STRUCT_H

#include <string>
#include <vector>
#include <memory>

struct AVLNode {
    std::string key;
    std::vector<std::string> translations;
    int balanceFactor;
    std::unique_ptr<AVLNode> left;
    std::unique_ptr<AVLNode> right;

    AVLNode(const std::string& word, const std::string& translation);
};

class AVLTree {
private:
    std::unique_ptr<AVLNode> root;

    void rotateLeft(std::unique_ptr<AVLNode>& node);
    void rotateRight(std::unique_ptr<AVLNode>& node);
    void balanceTree(std::unique_ptr<AVLNode>& node);
    void insert(std::unique_ptr<AVLNode>& node, const std::string& word, const std::string& translation);
    void remove(std::unique_ptr<AVLNode>& node, const std::string& word);
    AVLNode* findMin(AVLNode* node);
    int height(const std::unique_ptr<AVLNode>& node);
    void updateBalanceFactor(std::unique_ptr<AVLNode>& node);

public:
    AVLTree();
    void insert(const std::string& word, const std::string& translation);
    void remove(const std::string& word);
    std::vector<std::string> search(const std::string& word);
};

#endif // STRUCT_H

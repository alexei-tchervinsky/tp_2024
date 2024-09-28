#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <string>

namespace avl {

    class AVLTree {
    public:
        AVLTree();
        ~AVLTree() = default;

        void insert(const std::string& key, int row);
        bool search(const std::string& key) const;
        void remove(const std::string& key);
        void displayCrossReference() const;

    private:
        struct Node {
            std::string key;
            std::vector<int> occurrences;
            int balanceFactor;
            std::shared_ptr<Node> left;
            std::shared_ptr<Node> right;

            Node(const std::string& k, int row) :
                key(k), balanceFactor(0), left(nullptr), right(nullptr) {
                occurrences.push_back(row);
            }
        };

        std::shared_ptr<Node> root_;

        int height(const std::shared_ptr<Node>& node) const;
        int getBalance(const std::shared_ptr<Node>& node) const;
        std::shared_ptr<Node> rotateRight(std::shared_ptr<Node> y);
        std::shared_ptr<Node> rotateLeft(std::shared_ptr<Node> x);
        std::shared_ptr<Node> insertUtil(std::shared_ptr<Node> node, const std::string& key, int row);
        std::shared_ptr<Node> removeUtil(std::shared_ptr<Node> node, const std::string& key);
        std::shared_ptr<Node> minValueNode(const std::shared_ptr<Node>& node) const;
        bool searchUtil(const std::shared_ptr<Node>& node, const std::string& key) const;
        void displayCrossReferenceUtil(const std::shared_ptr<Node>& node) const;
    };

}

#endif
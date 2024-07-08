#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

namespace custom_dict
{
    enum Color { RED, BLACK };

    struct Node
    {
        std::string key;
        Color color;
        std::vector<std::string> translations;
        std::shared_ptr<Node> left, right, parent;

        Node(const std::string& k, const std::vector<std::string>& t)
        : key(k), color(RED), translations(t), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    class RedBlackTree
    {
        private:
        std::shared_ptr<Node> root;
        void leftRotate(std::shared_ptr<Node> x);
        void rightRotate(std::shared_ptr<Node> x);
        void insertFixUp(std::shared_ptr<Node> z);
        void deleteFixUp(std::shared_ptr<Node> x);
        std::shared_ptr<Node> minimum(std::shared_ptr<Node> node);
        void transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v);
        std::shared_ptr<Node> searchTreeHelper(std::shared_ptr<Node> node, const std::string& key) const;

        public:
        RedBlackTree() : root(nullptr) {}
        void insert(const std::string& key, const std::vector<std::string>& translations);
        std::vector<std::string> search(const std::string& key) const;
        void remove(const std::string& key);
    };
}

#endif

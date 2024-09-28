#include "AVLTree.hpp"

namespace avl {

    AVLTree::AVLTree() : root_(nullptr) {}

    void AVLTree::insert(const std::string& key, int row) {
        root_ = insertUtil(root_, key, row);
    }

    bool AVLTree::search(const std::string& key) const {
        return searchUtil(root_, key);
    }

    void AVLTree::remove(const std::string& key) {
        root_ = removeUtil(root_, key);
    }

    void AVLTree::displayCrossReference() const {
        displayCrossReferenceUtil(root_);
    }

    int AVLTree::height(const std::shared_ptr<Node>& node) const {
        if (!node) {
            return 0;
        }
        return std::max(height(node->left), height(node->right)) + 1;
    }

    int AVLTree::getBalance(const std::shared_ptr<Node>& node) const {
        if (!node) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    std::shared_ptr<AVLTree::Node> AVLTree::rotateRight(std::shared_ptr<Node> y) {
        auto x = y->left;
        auto T2 = x->right;

        x->right = y;
        y->left = T2;

        return x;
    }

    std::shared_ptr<AVLTree::Node> AVLTree::rotateLeft(std::shared_ptr<Node> x) {
        auto y = x->right;
        auto T2 = y->left;

        y->left = x;
        x->right = T2;

        return y;
    }

    std::shared_ptr<AVLTree::Node> AVLTree::insertUtil(std::shared_ptr<Node> node, const std::string& key, int row) {
        if (!node) {
            return std::make_shared<Node>(key, row);
        }

        if (key < node->key) {
            node->left = insertUtil(node->left, key, row);
        }
        else if (key > node->key) {
            node->right = insertUtil(node->right, key, row);
        }
        else {
            node->occurrences.push_back(row);
        }

        node->balanceFactor = getBalance(node);

        if (node->balanceFactor > 1 && key < node->left->key) {
            return rotateRight(node);
        }
        if (node->balanceFactor < -1 && key > node->right->key) {
            return rotateLeft(node);
        }
        if (node->balanceFactor > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (node->balanceFactor < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    std::shared_ptr<AVLTree::Node> AVLTree::minValueNode(const std::shared_ptr<Node>& node) const {
        auto current = node;
        while (current->left) {
            current = current->left;
        }
        return current;
    }

    std::shared_ptr<AVLTree::Node> AVLTree::removeUtil(std::shared_ptr<Node> node, const std::string& key) {
        if (!node) {
            return node;
        }

        if (key < node->key) {
            node->left = removeUtil(node->left, key);
        }
        else if (key > node->key) {
            node->right = removeUtil(node->right, key);
        }
        else {
            if (!node->left || !node->right) {
                node = (node->left) ? node->left : node->right;
            }
            else {
                auto temp = minValueNode(node->right);
                node->key = temp->key;
                node->occurrences = temp->occurrences;
                node->right = removeUtil(node->right, temp->key);
            }
        }

        if (!node) {
            return node;
        }

        node->balanceFactor = getBalance(node);

        if (node->balanceFactor > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }
        if (node->balanceFactor > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (node->balanceFactor < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }
        if (node->balanceFactor < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    bool AVLTree::searchUtil(const std::shared_ptr<Node>& node, const std::string& key) const {
        if (!node) {
            return false;
        }
        if (key == node->key) {
            return true;
        }
        if (key < node->key) {
            return searchUtil(node->left, key);
        }
        return searchUtil(node->right, key);
    }

    void AVLTree::displayCrossReferenceUtil(const std::shared_ptr<Node>& node) const {
        if (!node) {
            return;
        }
        displayCrossReferenceUtil(node->left);
        std::cout << "Word: " << node->key << ", Occurrences: ";
        for (const auto& row : node->occurrences) {
            std::cout << row << " ";
        }
        std::cout << std::endl;
        displayCrossReferenceUtil(node->right);
    }

}
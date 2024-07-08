#include "commands.hpp"

namespace custom_dict
{
    void RedBlackTree::leftRotate(std::shared_ptr<Node> x)
    {
        auto y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void RedBlackTree::rightRotate(std::shared_ptr<Node> x)
    {
        auto y = x->left;
        x->left = y->right;
        if (y->right != nullptr) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void RedBlackTree::insertFixUp(std::shared_ptr<Node> z)
    {
        while (z->parent != nullptr && z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                auto y = z->parent->parent->right;
                if (y != nullptr && y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else
            {
                auto y = z->parent->parent->left;
                if (y != nullptr && y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void RedBlackTree::transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v)
    {
        if (u->parent == nullptr) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v != nullptr) v->parent = u->parent;
    }

    std::shared_ptr<Node> RedBlackTree::minimum(std::shared_ptr<Node> node)
    {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    void RedBlackTree::deleteFixUp(std::shared_ptr<Node> x)
    {
        while (x != root && (x == nullptr || x->color == BLACK))
        {
            if (x == x->parent->left)
            {
                auto w = x->parent->right;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if ((w->left == nullptr || w->left->color == BLACK) && (w->right == nullptr || w->right->color == BLACK))
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right == nullptr || w->right->color == BLACK)
                    {
                        if (w->left != nullptr) w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->right != nullptr) w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                auto w = x->parent->left;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if ((w->left == nullptr || w->left->color == BLACK) && (w->right == nullptr || w->right->color == BLACK))
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->left == nullptr || w->left->color == BLACK)
                    {
                        if (w->right != nullptr) w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->left != nullptr) w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr) x->color = BLACK;
    }

    void RedBlackTree::insert(const std::string& key, const std::vector<std::string>& translations)
    {
        auto z = std::make_shared<Node>(key, translations);
        std::shared_ptr<Node> y = nullptr;
        auto x = root;

        while (x != nullptr)
        {
            y = x;
            if (z->key < x->key) x = x->left;
            else x = x->right;
        }
        z->parent = y;

        if (y == nullptr) root = z;
        else if (z->key < y->key) y->left = z;
        else y->right = z;

        insertFixUp(z);
    }

    std::vector<std::string> RedBlackTree::search(const std::string& key) const
    {
        auto node = searchTreeHelper(root, key);
        if (node != nullptr) return node->translations;
        else throw std::invalid_argument("Ключ не найден");
    }

    std::shared_ptr<Node> RedBlackTree::searchTreeHelper(std::shared_ptr<Node> node, const std::string& key) const
    {
        if (node == nullptr || key == node->key) return node;
        if (key < node->key) return searchTreeHelper(node->left, key);
        return searchTreeHelper(node->right, key);
    }

    void RedBlackTree::remove(const std::string& key)
    {
        auto z = searchTreeHelper(root, key);
        if (z == nullptr) throw std::invalid_argument("Ключ не найден");
    
        auto y = z;
        auto yOriginalColor = y->color;
        std::shared_ptr<Node> x;

        if (z->left == nullptr)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nullptr)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z)
            {
                if (x != nullptr) x->parent = y;
            }
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right != nullptr) y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr) y->left->parent = y;
            y->color = z->color;
        }
        if (yOriginalColor == BLACK) deleteFixUp(x);
    }
}

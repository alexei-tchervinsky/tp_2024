#include "avl_tree.h"
#include <iostream>
#include <string>

int main() {
    AVLTree dictionary;
    std::string command;
    std::string word, translation;

    while (std::cin) {
        std::cout << "Enter command (insert, remove, search) or Ctrl+D to exit: ";
        std::cin >> command;
        if (command == "insert") {
            std::cout << "Enter word: ";
            std::cin >> word;
            std::cout << "Enter translation: ";
            std::cin >> translation;
            executeInsert(dictionary, word, translation);
        }
        else if (command == "remove") {
            std::cout << "Enter word: ";
            std::cin >> word;
            executeRemove(dictionary, word);
        }
        else if (command == "search") {
            std::cout << "Enter word: ";
            std::cin >> word;
            executeSearch(dictionary, word);
        }
    }

    return 0;
}

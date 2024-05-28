#include "avl_tree.h"
#include <iostream>

void executeInsert(AVLTree& tree, const std::string& word, const std::string& translation) {
    tree.insert(word, translation);
    std::cout << "Inserted: " << word << " -> " << translation << std::endl;
}

void executeRemove(AVLTree& tree, const std::string& word) {
    tree.remove(word);
    std::cout << "Removed: " << word << std::endl;
}

void executeSearch(AVLTree& tree, const std::string& word) {
    std::vector<std::string> translations = tree.search(word);
    if (translations.empty()) {
        std::cout << "Word '" << word << "' was not found." << std::endl;
    }
    else {
        std::cout << "Translation for the word '" << word << "':" << std::endl;
        for (const auto& translation : translations) {
            std::cout << translation << std::endl;
        }
    }
}

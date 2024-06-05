// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "two_three_tree.h"
#include <iostream>
#include <string>

int main() {
    TwoThreeTree dictionary;  // Initialize the 2-3 tree for the dictionary
    std::string command, word, translation;
    std::vector<std::string> translations;

    while (true) {
        std::cout << "\n--- Dictionary Management SystemEN/RU ---\n";
        std::cout << "1. Insert Word\n";
        std::cout << "2. Search Word\n";
        std::cout << "3. Delete Word\n";
        std::cout << "4. Print Dictionary\n";
        std::cout << "q. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> command;

        if (command == "q" || command == "Q") {
            break;
        }

        switch (command[0]) {
        case '1':
            std::cout << "Enter the word to insert: ";
            std::cin >> word;
            std::cout << "Enter its translation: ";
            std::cin >> translation;
            translations.clear();
            translations.push_back(translation);
            dictionary.insert(word, translations);
            std::cout << "Word inserted!\n";
            break;
        case '2':
            std::cout << "Enter the word to search: ";
            std::cin >> word;
            if (dictionary.search(word)) {
                std::cout << "Word found: " << word << std::endl;
            }
            else {
                std::cout << "Word not found!\n";
            }
            break;
        case '3':
            std::cout << "Enter the word to delete: ";
            std::cin >> word;
            dictionary.deleteKey(word);
            std::cout << "Word deleted (if it was in the dictionary).\n";
            break;
        case '4':
            std::cout << "Current Dictionary:\n";
            dictionary.printTree();
            break;
        default:
            std::cout << "Invalid choice. Please choose again.\n";
            break;
        }
    }

    std::cout << "Exiting Dictionary Management System.\n";
    return 0;
}


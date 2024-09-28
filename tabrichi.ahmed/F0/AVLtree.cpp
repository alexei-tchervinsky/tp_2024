#include "AVLTree.hpp"
#include <iostream>
#include <sstream>
#include <string>

void displayHelp() {
    std::cout << "Commands:\n"
        << "  insert <word> <line_number>   - Insert a word at the given line number\n"
        << "  search <word>                - Search for a word\n"
        << "  remove <word>                - Remove a word\n"
        << "  display                      - Display cross-reference table\n"
        << "  exit                         - Exit the program\n";
}

int main() {
    avl::AVLTree tree;
    std::string command;

    displayHelp();
    std::cout << "\n> ";

    while (std::getline(std::cin, command)) {
        std::istringstream iss(command);
        std::string action, word;
        int lineNumber;

        iss >> action;
        if (action == "insert") {
            iss >> word >> lineNumber;
            tree.insert(word, lineNumber);
        }
        else if (action == "search") {
            iss >> word;
            if (tree.search(word)) {
                std::cout << "'" << word << "' found in the tree.\n";
            }
            else {
                std::cout << "'" << word << "' not found.\n";
            }
        }
        else if (action == "remove") {
            iss >> word;
            tree.remove(word);
        }
        else if (action == "display") {
            tree.displayCrossReference();
        }
        else if (action == "help") {
            displayHelp();
        }
        else if (action == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command. Type 'help' for a list of commands.\n";
        }

        std::cout << "\n> ";
    }

    return 0;
}
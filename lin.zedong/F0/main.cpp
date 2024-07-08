#include "commands.hpp"
#include <iostream>
#include <sstream>

using namespace custom_dict;

void displayMenu()
{
    std::cout << "Commands:\n";
    std::cout << "1. INSERT <слово> <перевод1> <перевод2> ... <переводN>\n";
    std::cout << "2. SEARCH <слово>\n";
    std::cout << "3. DELETE <слово>\n";
    std::cout << "4. EXIT\n";
}

void processInsert(RedBlackTree& tree, const std::string& input)
{
    std::istringstream iss(input);
    std::string command, word, translation;
    std::vector<std::string> translations;
    iss >> command >> word;
    while (iss >> translation)
    {
        translations.push_back(translation);
    }
    tree.insert(word, translations);
    std::cout << "Inserted: " << word << std::endl;
}

void processSearch(const RedBlackTree& tree, const std::string& input)
{
    std::istringstream iss(input);
    std::string command, word;
    iss >> command >> word;
    try
    {
        auto translations = tree.search(word);
        std::cout << "Переводы для " << word << ": ";
        for (const auto& t : translations)
        {
            std::cout << t << " ";
        }
        std::cout << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void processDelete(RedBlackTree& tree, const std::string& input)
{
    std::istringstream iss(input);
    std::string command, word;
    iss >> command >> word;
    try
    {
        tree.remove(word);
        std::cout << "Deleted: " << word << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    RedBlackTree tree;
    std::string input;

    displayMenu();
    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "EXIT") break;
        if (input.find("INSERT") == 0)
        {
            processInsert(tree, input);
        }
        else if (input.find("SEARCH") == 0)
        {
            processSearch(tree, input);
        }
        else if (input.find("DELETE") == 0)
        {
            processDelete(tree, input);
        }
        else
        {
            std::cout << "Неизвестная команда" << std::endl;
        }
    }

    return 0;
}

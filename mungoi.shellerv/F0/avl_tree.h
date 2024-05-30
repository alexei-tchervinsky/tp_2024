#ifndef Cavl_tree_H
#define avl_tree_H

#include "struct.h"
#include <string>
#include <vector>

void executeInsert(AVLTree& tree, const std::string& word, const std::string& translation);
void executeRemove(AVLTree& tree, const std::string& word);
void executeSearch(AVLTree& tree, const std::string& word);

#endif // COMMANDS_H

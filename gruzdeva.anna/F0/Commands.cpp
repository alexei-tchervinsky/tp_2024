#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>

#include "Commands.hpp"

// dictionary is a structure (map) that contains words and lines where they are found
// std::map<std::string, std::list<int>> dictionary;

namespace commands {
  void help(std::ostream& os) {
    os << "===============================================================\n";
    os << "Available commands:\n";
    os << "1. HELP - show list of all available commands\n";
    os << "2. LIST - show list of all dictionaries\n";
    os << "3. CREATE <filename> - create a new reference dictionary, based on text from the given file\n";
    os << "4. RENAME <new dictionary_name> <dictionary_name> - rename the dictionary\n";
    os << "4. DELETE <dictionary_name> - delete the dictionary with given name\n";
    os << "for the following commands you need to have a dictionary selected (use command 5)\n";
    os << "5. USE <dictionary_name> - use the dictionary, based on the given file\n";
    os << "6. COUNT - show the number of words in the dictionary\n";
    os << "7. PRINT - show content of the dictionary\n";
    os << "8. SEARCH <word> - search for the word in the dictionary\n";
    os << "9. REMOVE <word> - remove the word from the dictionary\n";
    os << "10. SAVE <filename> - save the dictionary to the file\n";
    os << "===============================================================\n\n";
  }

  void getAllDictionaries(const std::map<std::string, std::shared_ptr<std::map<std::string,
                          std::list<int>>>>& dictionaries, std::ostream& os) {
    if (dictionaries.empty()) {
      os << "No dictionaries found.\n";
      return;
    }

    os << "===============================================================\n";
    os << "List of all dictionaries:\n";
    std::transform(dictionaries.begin(), dictionaries.end(),
                   std::ostream_iterator<std::string>(os, "\n"),
                   [](const std::pair<std::string, std::shared_ptr<std::map<std::string,
                       std::list<int>>>>& pair){
                    return pair.first;
                    });
  }

  void create(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
              std::string& currentDict, std::istream& is, std::ostream& os) {
    std::map<std::string, std::list<int>> dictionary;
    std::string filename;
    is >> filename;
    if (filename.empty() || is.get() != '\n') {
      throw std::invalid_argument("Error: wrong number of arguments.");
    }
    std::ifstream file(filename);
    if (!file) {
      throw std::invalid_argument("Error: cannot open the file.");
    }

    std::string line;
    int lineNum = 1;
    std::string delimiters = " !?.,|/;:(){}\"\\";
    while (!file.eof()) {
      std::getline(file, line);
      os << lineNum << " " << line << "\n";

      // Replace delimiters with spaces
      std::transform(line.begin(), line.end(), line.begin(),
                     [&delimiters](char c) {
                         return delimiters.find(c) != std::string::npos ? ' ' : c;
                     }
      );
      std::istringstream lineStream(line);

      std::string word;
      while (lineStream >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        dictionary[word].push_back(lineNum);
      }
      ++lineNum;
    }

    std::shared_ptr<std::map<std::string, std::list<int>>> dictionaryPtr = std::make_shared<std::map<std::string,
    std::list<int>>>(dictionary);
    dictionaries[filename] = dictionaryPtr;
    currentDict = filename;
    os << "\nDictionary has been created.\n";
  }

  void rename(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
              std::istream& is, std::ostream& os) {
    std::string newname, oldname;
    is >> newname >> oldname;
    if (newname.empty() || oldname.empty() || is.get() != '\n') {
      throw std::invalid_argument("Error: wrong number of arguments.");
    }

    auto it = dictionaries.find(oldname);
    if (it == dictionaries.end()) {
      throw std::invalid_argument("Error: dictionary not found.");
    }
    else {
      std::shared_ptr<std::map<std::string, std::list<int>>> dictionaryPtr = it->second;
      dictionaries.erase(it);
      dictionaries[newname] = dictionaryPtr;
      os << "Dictionary has been renamed.\n";
    }
  }

  void del(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
           std::istream& is, std::ostream& os) {
    std::string dictname;
    is >> dictname;
    if (dictname.empty() || is.get() != '\n') {
      throw std::invalid_argument("Error: wrong number of arguments.");
    }

    auto it = dictionaries.find(dictname);
    if (it == dictionaries.end()) {
      throw std::invalid_argument("Error: dictionary not found.");
    }
    else {
      it->second->clear();
      dictionaries.erase(it);
      os << "Dictionary has been deleted.\n";
    }
  }

  void changeCurrentDictionary(
      std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
      std::string& currentDict, std::istream& is, std::ostream& os) {
    std::string dictname;
    is >> dictname;
    if (dictname.empty() || is.get() != '\n') {
      throw std::invalid_argument("Error: wrong number of arguments.");
    }

    auto it = dictionaries.find(dictname);
    if (it == dictionaries.end()) {
      throw std::invalid_argument("Error: dictionary not found.");
    }
    else {
      currentDict = dictname;
      os << "Dictionary has been selected.\n";
    }
  }

  void count(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
             const std::string& currentDict, std::ostream& os) {
    auto dictionary = *dictionaries.find(currentDict)->second;
    os << "Number of words in the dictionary: " << dictionary.size() << "\n";
  }

  void search(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
              const std::string& currentDict, std::istream& is, std::ostream& os) {
    std::string word;
    is >> word;
    if (word.empty() || is.get() != '\n') {
      throw std::invalid_argument("Error: wrong number of arguments.");
    }

    auto dictionary = *dictionaries.find(currentDict)->second;
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    auto it = dictionary.find(word);
    if (it == dictionary.end()) {
      os << "Word not found.\n";
    }
    else {
      os << word << " : ";
      std::copy(it->second.begin(), it->second.end(), std::ostream_iterator<int>(os, " "));
      os << "\n";
    }
  }

  void print(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
             const std::string& currentDict, std::ostream& os) {
    auto dictionary = *dictionaries.find(currentDict)->second;
    if (dictionary.empty()) {
      throw std::logic_error("Error: dictionary is empty.");
    }

    os << "Dictionary format: <word> : <line numbers>\n";
    std::transform(dictionary.begin(), dictionary.end(),
                   std::ostream_iterator<std::string>(os, "\n"),
                   [](const std::pair<std::string, std::list<int>>& pair) {
                       std::ostringstream oss;
                       oss << pair.first << " : ";
                       std::copy(pair.second.begin(), pair.second.end(),
                                 std::ostream_iterator<int>(oss, " "));
                       return oss.str();
                   });
  }

  void remove(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
              std::string& currentDict, std::istream& is, std::ostream& os) {
    std::string word;
    is >> word;
    if (word.empty() || is.get() != '\n') {
      throw std::invalid_argument("Error: wrong number of arguments.");
    }

    auto dictionary = *dictionaries.find(currentDict)->second;
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    auto it = dictionary.find(word);
    if (it == dictionary.end()) {
      throw std::invalid_argument("Error: word not found.");
    }
    else {
      dictionary.erase(it);
      os << "\"" << word << "\" has been removed from the dictionary.\n";
    }
  }

  void save(std::map<std::string, std::shared_ptr<std::map<std::string, std::list<int>>>>& dictionaries,
            const std::string& currentDict, std::istream& is, std::ostream& os) {
    std::string filename;
    is >> filename;
    if (filename.empty() || is.get() != '\n') {
      throw std::invalid_argument("Error: wrong number of arguments.");
    }

    std::ofstream file(filename);
    if (!file) {
      throw std::invalid_argument("Error: cannot open the file.");
    }

    auto dictionary = *dictionaries.find(currentDict)->second;
    std::transform(dictionary.begin(), dictionary.end(),
                   std::ostream_iterator<std::string>(file, "\n"),
                   [](const std::pair<std::string, std::list<int>>& pair) {
                    std::ostringstream oss;
                    oss << pair.first << " : ";
                    std::copy(pair.second.begin(), pair.second.end(),
                              std::ostream_iterator<int>(oss, " "));
                    return oss.str();
                    });
    os << "Dictionary has been saved to the file:\"" << filename << "\".\n";
  }

  std::ostream& outError(std::ostream& os, const std::string& message) {
    os << message << "\n";
    return os;
  }
}

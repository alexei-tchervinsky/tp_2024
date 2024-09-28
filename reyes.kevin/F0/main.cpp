#include "struct.hpp"
#include <io.h>
#include <fcntl.h>

int main() {
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin), _O_U8TEXT);

    TranslationMap dict;

    std::wcout << L"> Enter commands (INSERT, SEARCH, REMOVE, DISPLAY, EXIT, HELP):\n";

    std::wstring command;
    while (std::wcin >> command) {
        if (command == L"INSERT") {
            std::wcout << L"> Enter a new word, then the translation:\n";
            std::wstring key, value;
            std::wcin >> key >> value;
            insertTranslation(dict, key, value);
        }
        else if (command == L"SEARCH") {
            std::wcout << L"> Enter the word you are looking for:\n";
            std::wstring key;
            std::wcin >> key;
            std::list<std::wstring> translations = searchTranslation(dict, key);
            if (!translations.empty()) {
                std::wcout << L"> Translations for '" << key << L"': ";
                for (const auto& translation : translations) {
                    std::wcout << translation << L" ";
                }
                std::wcout << std::endl;
            }
            else {
                std::wcout << L"> No translations found for '" << key << L"'.\n";
            }
        }
        else if (command == L"REMOVE") {
            std::wcout << L"> Enter the word you want to delete:\n";
            std::wstring key;
            std::wcin >> key;
            removeTranslation(dict, key);
        }
        else if (command == L"DISPLAY") {
            std::wcout << L"> These are the words in the dictionary\n";
            displayTranslations(dict);
        }
        else if (command == L"HELP") {
            std::wcout << L"> (INSERT) Adds new words to the dictionary. Example: INSERT -> apple (new_word) -> яблоко (translation)\n";
            std::wcout << L"> (SEARCH) Allows you search for a word in the dictionary. Example: SEARCH -> apple\n";
            std::wcout << L"> (REMOVE) Deletes an existing word. Example: REMOVE -> apple\n";
            std::wcout << L"> (DISPLAY) Shows the words in the dictionary\n";
            std::wcout << L"> (EXIT) Finish the program\n";
        }
        else if (command == L"EXIT") {
            break;
        }
        else {
            std::wcout << L"> Unknown command\n";
        }
    }

    return 0;
}

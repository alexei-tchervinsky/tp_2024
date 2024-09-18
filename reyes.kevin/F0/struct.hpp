#include <iostream>
#include <unordered_map>
#include <string>
#include <list>
#include <algorithm>
#include <memory>
#include <sstream>

using TranslationMap = std::unordered_map<std::wstring, std::list<std::wstring>>;

void insertTranslation(TranslationMap& dict, const std::wstring& key, const std::wstring& value) {
    dict[key].push_back(value);
    dict[key].sort();
    dict[key].unique();
}

std::list<std::wstring> searchTranslation(const TranslationMap& dict, const std::wstring& key) {
    auto it = dict.find(key);
    if (it != dict.end()) {
        return it->second;
    }
    return {};
}

void removeTranslation(TranslationMap& dict, const std::wstring& key) {
    dict.erase(key);
}

void displayTranslations(const TranslationMap& dict) {
    for (const auto& entry : dict) {
        std::wcout << entry.first << L" -> [";
        for (const auto& value : entry.second) {
            std::wcout << value << L"";
        }
        std::wcout << L"]\n";
    }
}

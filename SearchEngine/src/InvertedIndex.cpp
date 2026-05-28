#include "InvertedIndex.h"
#include <algorithm>
#include <cctype>

// Реализация Singleton
InvertedIndex& InvertedIndex::getInstance() {
    static InvertedIndex instance;
    return instance;
}

void InvertedIndex::addWord(const std::string& word, int docId) {
    std::string lowerWord = word;
    std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    auto& docs = index[lowerWord];

    if (std::find(docs.begin(), docs.end(), docId) == docs.end()) {
        docs.push_back(docId);
    }
}

std::vector<int> InvertedIndex::getDocuments(const std::string& word) const {
    std::string lowerWord = word;
    std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    auto it = index.find(lowerWord);
    if (it != index.end()) {
        return it->second;
    }
    return {};
}

void InvertedIndex::clear() {
    index.clear();
}

std::vector<std::string> InvertedIndex::getAllWords() const {
    std::vector<std::string> words;
    for (const auto& [word, _] : index) {
        words.push_back(word);
    }
    return words;
}

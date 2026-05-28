#include "SearchStrategy.h"
#include "InvertedIndex.h"
#include "Levenshtein.h"
#include <map>
#include <algorithm>
#include <cctype>

std::vector<int> ExactSearchStrategy::search(const std::string& query, int /*maxDistance*/) {
    return InvertedIndex::getInstance().getDocuments(query);
}

std::vector<int> FuzzySearchStrategy::search(const std::string& query, int maxDistance) {
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    InvertedIndex& index = InvertedIndex::getInstance();
    auto allWords = index.getAllWords();

    std::map<int, int> documentScore;

    for (const auto& word : allWords) {
        if (Levenshtein::distance(word, lowerQuery) <= maxDistance) {
            auto docIds = index.getDocuments(word);
            for (int docId : docIds) {
                documentScore[docId]++;
            }
        }
    }

    std::vector<std::pair<int, int>> sortedScores(documentScore.begin(), documentScore.end());
    std::sort(sortedScores.begin(), sortedScores.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    std::vector<int> results;
    for (const auto& [docId, _] : sortedScores) {
        results.push_back(docId);
    }

    return results;
}

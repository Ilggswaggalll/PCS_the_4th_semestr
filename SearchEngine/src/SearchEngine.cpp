#include "SearchEngine.h"
#include "InvertedIndex.h"

SearchEngine::SearchEngine()
    : strategy(std::make_unique<ExactSearchStrategy>()) {}

void SearchEngine::setStrategy(std::unique_ptr<SearchStrategy> newStrategy) {
    strategy = std::move(newStrategy);
}

void SearchEngine::loadFolder(const std::string& folderPath) {
    InvertedIndex& index = InvertedIndex::getInstance();
    indexer.indexFolder(folderPath, index, documents);
}

std::vector<int> SearchEngine::search(const std::string& query, int maxDistance) {
    if (!strategy) {
        return {};
    }
    return strategy->search(query, maxDistance);
}

const std::vector<Document>& SearchEngine::getDocuments() const {
    return documents;
}

std::string SearchEngine::getDocumentContent(int id) const {
    for (const auto& doc : documents) {
        if (doc.getId() == id) {
            return doc.getContent();
        }
    }
    return "";
}

std::string SearchEngine::getDocumentPath(int id) const {
    for (const auto& doc : documents) {
        if (doc.getId() == id) {
            return doc.getFilePath();
        }
    }
    return "";
}

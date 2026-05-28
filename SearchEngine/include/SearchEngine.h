#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Document.h"
#include "Indexer.h"
#include "SearchStrategy.h"

class SearchEngine {
private:
    std::vector<Document> documents;
    Indexer indexer;
    std::unique_ptr<SearchStrategy> strategy;

public:
    SearchEngine();

    void setStrategy(std::unique_ptr<SearchStrategy> newStrategy);
    void loadFolder(const std::string& folderPath);
    std::vector<int> search(const std::string& query, int maxDistance = 3);

    const std::vector<Document>& getDocuments() const;
    std::string getDocumentContent(int id) const;
    std::string getDocumentPath(int id) const;
};

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Document.h"
#include "DocumentFactory.h"
#include "IndexObserver.h"
#include "InvertedIndex.h"

class Indexer {
private:
    std::unique_ptr<DocumentFactory> factory;
    std::vector<std::unique_ptr<IndexObserver>> observers;

    std::vector<std::string> tokenize(const std::string& text);
    std::vector<Document> loadDocumentsFromFolder(const std::string& folderPath);
    void notifyObservers(const std::string& folderPath, int documentCount);

public:
    Indexer();

    void setFactory(std::unique_ptr<DocumentFactory> newFactory);
    void addObserver(std::unique_ptr<IndexObserver> observer);

    void indexDocument(const Document& doc, InvertedIndex& index);
    void indexFolder(const std::string& folderPath, InvertedIndex& index, std::vector<Document>& documentsOut);
};

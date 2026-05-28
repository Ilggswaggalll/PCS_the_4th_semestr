#pragma once
#include <string>
#include "Document.h"

// Абстрактная фабрика
class DocumentFactory {
public:
    virtual ~DocumentFactory() = default;
    virtual Document createDocument(int id, const std::string& content, const std::string& filePath) = 0;
};

// Фабрика для текстовых документов
class TextDocumentFactory : public DocumentFactory {
public:
    Document createDocument(int id, const std::string& content, const std::string& filePath) override;
};

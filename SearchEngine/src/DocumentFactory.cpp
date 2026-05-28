#include "DocumentFactory.h"

Document TextDocumentFactory::createDocument(int id, const std::string& content, const std::string& filePath) {
    return Document(id, content, filePath);
}

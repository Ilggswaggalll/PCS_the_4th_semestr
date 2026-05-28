#include "Document.h"

Document::Document(int id, const std::string& content, const std::string& filePath)
    : id(id), content(content), filePath(filePath) {}

int Document::getId() const {
    return id;
}

std::string Document::getContent() const {
    return content;
}

std::string Document::getFilePath() const {
    return filePath;
}

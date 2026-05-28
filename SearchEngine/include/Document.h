#pragma once
#include <string>

class Document {
private:
    int id;
    std::string content;
    std::string filePath;  // ДОБАВЛЯЕМ

public:
    Document(int id, const std::string& content, const std::string& filePath = "");

    int getId() const;
    std::string getContent() const;
    std::string getFilePath() const;  // ДОБАВЛЯЕМ
};

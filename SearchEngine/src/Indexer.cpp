#include "Indexer.h"
#include "DocumentFactory.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

// Подключаем Qt для работы с Unicode
#include <QString>
#include <QLocale>

namespace fs = std::filesystem;

// Конструктор - создаём фабрику по умолчанию
Indexer::Indexer() : factory(std::make_unique<TextDocumentFactory>()) {}

void Indexer::setFactory(std::unique_ptr<DocumentFactory> newFactory) {
    factory = std::move(newFactory);
}

void Indexer::addObserver(std::unique_ptr<IndexObserver> observer) {
    observers.push_back(std::move(observer));
}

void Indexer::notifyObservers(const std::string& folderPath, int documentCount) {
    for (const auto& observer : observers) {
        observer->onIndexUpdated(folderPath, documentCount);
    }
}

std::vector<std::string> Indexer::tokenize(const std::string& text) {
    std::vector<std::string> words;

    // Конвертируем UTF-8 строку в QString (Qt умеет работать с Unicode)
    QString qText = QString::fromStdString(text);

    QString currentWord;

    for (int i = 0; i < qText.size(); ++i) {
        QChar ch = qText[i];

        // Проверяем, является ли символ буквой (работает с русскими буквами!)
        if (ch.isLetter()) {
            currentWord.append(ch);
        } else if (!currentWord.isEmpty()) {
            // Приводим к нижнему регистру и добавляем
            words.push_back(currentWord.toLower().toStdString());
            currentWord.clear();
        }
    }

    if (!currentWord.isEmpty()) {
        words.push_back(currentWord.toLower().toStdString());
    }

    // Отладка
    static bool debugPrinted = false;
    if (!debugPrinted && !words.empty()) {
        std::cout << "DEBUG: Found " << words.size() << " words. First 10:" << std::endl;
        for (size_t i = 0; i < std::min(words.size(), size_t(10)); ++i) {
            std::cout << "  '" << words[i] << "'" << std::endl;
        }
        debugPrinted = true;
    }

    return words;
}

std::vector<Document> Indexer::loadDocumentsFromFolder(const std::string& folderPath) {
    std::vector<Document> docs;
    int docId = 0;

    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cout << "Folder does not exist: " << folderPath << std::endl;
        return docs;
    }

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::ifstream file(entry.path());
            if (file.is_open()) {
                std::stringstream buffer;
                buffer << file.rdbuf();
                std::string content = buffer.str();
                // ИСПОЛЬЗУЕМ ФАБРИКУ ДЛЯ СОЗДАНИЯ ДОКУМЕНТА
                docs.push_back(factory->createDocument(docId++, content, entry.path().string()));
                file.close();
                std::cout << "Loaded: " << entry.path().filename().string() << std::endl;
            }
        }
    }

    std::cout << "Total documents loaded: " << docs.size() << std::endl;
    return docs;
}

void Indexer::indexDocument(const Document& doc, InvertedIndex& index) {
    auto words = tokenize(doc.getContent());
    for (const auto& word : words) {
        index.addWord(word, doc.getId());
    }
}

void Indexer::indexFolder(const std::string& folderPath, InvertedIndex& index, std::vector<Document>& documentsOut) {
    // Очищаем старый индекс
    index.clear();
    documentsOut.clear();

    // Загружаем документы
    auto docs = loadDocumentsFromFolder(folderPath);

    // Индексируем каждый документ
    for (const auto& doc : docs) {
        documentsOut.push_back(doc);
        indexDocument(doc, index);
    }

    std::cout << "Indexing complete. Unique words in index: " << index.getAllWords().size() << std::endl;

    // Уведомляем наблюдателей
    notifyObservers(folderPath, documentsOut.size());
}

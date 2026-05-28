#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class InvertedIndex {
private:
    // Приватный конструктор (Singleton)
    InvertedIndex() = default;

    // Запрещаем копирование и присваивание
    InvertedIndex(const InvertedIndex&) = delete;
    InvertedIndex& operator=(const InvertedIndex&) = delete;

    std::unordered_map<std::string, std::vector<int>> index;

public:
    // Получить единственный экземпляр
    static InvertedIndex& getInstance();

    // Добавить слово для документа
    void addWord(const std::string& word, int docId);

    // Получить список документов по слову
    std::vector<int> getDocuments(const std::string& word) const;

    // Очистить весь индекс
    void clear();

    // Получить все слова в индексе для fuzzy search
    std::vector<std::string> getAllWords() const;
};

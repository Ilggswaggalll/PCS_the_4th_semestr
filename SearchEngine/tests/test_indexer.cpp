#include <catch2/catch_test_macros.hpp>
#include "Indexer.h"
#include "InvertedIndex.h"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

TEST_CASE("Indexer: индексирует файл", "[indexer]") {

    Indexer indexer;

    auto& index = InvertedIndex::getInstance();

    index.clear();

    fs::create_directories("temp");

    std::ofstream file("temp/test.txt");

    file << "hello world";

    file.close();

    std::vector<Document> docs;

    indexer.indexFolder("temp", index, docs);

    REQUIRE(index.getDocuments("hello").size() == 1);
    REQUIRE(index.getDocuments("world").size() == 1);

    fs::remove_all("temp");
}

TEST_CASE("Indexer: пустая папка", "[indexer]") {

    Indexer indexer;

    auto& index = InvertedIndex::getInstance();

    index.clear();

    fs::create_directories("empty");

    std::vector<Document> docs;

    indexer.indexFolder("empty", index, docs);

    REQUIRE(docs.empty());

    fs::remove_all("empty");
}

TEST_CASE("Indexer: несколько файлов", "[indexer]") {

    Indexer indexer;

    auto& index = InvertedIndex::getInstance();

    index.clear();

    fs::create_directories("multi");

    std::ofstream("multi/a.txt") << "cat";
    std::ofstream("multi/b.txt") << "dog";

    std::vector<Document> docs;

    indexer.indexFolder("multi", index, docs);

    REQUIRE(docs.size() == 2);

    fs::remove_all("multi");
}

TEST_CASE("Indexer: повтор слова", "[indexer]") {

    Indexer indexer;

    auto& index = InvertedIndex::getInstance();

    index.clear();

    fs::create_directories("repeat");

    std::ofstream("repeat/test.txt")
        << "hello hello hello";

    std::vector<Document> docs;

    indexer.indexFolder("repeat", index, docs);

    REQUIRE(index.getDocuments("hello").size() >= 1);

    fs::remove_all("repeat");
}

TEST_CASE("Indexer: разные слова", "[indexer]") {

    Indexer indexer;

    auto& index = InvertedIndex::getInstance();

    index.clear();

    fs::create_directories("words");

    std::ofstream("words/test.txt")
        << "apple banana orange";

    std::vector<Document> docs;

    indexer.indexFolder("words", index, docs);

    REQUIRE(index.getDocuments("apple").size() == 1);
    REQUIRE(index.getDocuments("banana").size() == 1);

    fs::remove_all("words");
}

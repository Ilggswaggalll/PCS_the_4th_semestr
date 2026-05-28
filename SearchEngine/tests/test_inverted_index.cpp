#include <catch2/catch_test_macros.hpp>
#include "InvertedIndex.h"

TEST_CASE("InvertedIndex: Singleton", "[index]") {

    auto& i1 = InvertedIndex::getInstance();
    auto& i2 = InvertedIndex::getInstance();

    REQUIRE(&i1 == &i2);
}

TEST_CASE("InvertedIndex: добавление слова", "[index]") {

    auto& index = InvertedIndex::getInstance();

    index.clear();

    index.addWord("hello", 1);

    auto docs = index.getDocuments("hello");

    REQUIRE(docs.size() == 1);
    REQUIRE(docs[0] == 1);
}

TEST_CASE("InvertedIndex: несколько документов", "[index]") {

    auto& index = InvertedIndex::getInstance();

    index.clear();

    index.addWord("hello", 1);
    index.addWord("hello", 2);

    auto docs = index.getDocuments("hello");

    REQUIRE(docs.size() == 2);
}

TEST_CASE("InvertedIndex: отсутствующее слово", "[index]") {

    auto& index = InvertedIndex::getInstance();

    index.clear();

    auto docs = index.getDocuments("missing");

    REQUIRE(docs.empty());
}

TEST_CASE("InvertedIndex: clear очищает индекс", "[index]") {

    auto& index = InvertedIndex::getInstance();

    index.clear();

    index.addWord("hello", 1);

    index.clear();

    REQUIRE(index.getDocuments("hello").empty());
}

TEST_CASE("InvertedIndex: несколько слов", "[index]") {

    auto& index = InvertedIndex::getInstance();

    index.clear();

    index.addWord("cat", 1);
    index.addWord("dog", 2);

    REQUIRE(index.getDocuments("cat").size() == 1);
    REQUIRE(index.getDocuments("dog").size() == 1);
}

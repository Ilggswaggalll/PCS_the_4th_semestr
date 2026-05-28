#include <catch2/catch_test_macros.hpp>
#include "Document.h"

TEST_CASE("Document: создание с путём", "[document]") {

    Document doc(5, "content", "/path/file.txt");

    REQUIRE(doc.getId() == 5);
    REQUIRE(doc.getContent() == "content");
    REQUIRE(doc.getFilePath() == "/path/file.txt");
}

TEST_CASE("Document: создание без пути", "[document]") {

    Document doc(1, "text");

    REQUIRE(doc.getId() == 1);
    REQUIRE(doc.getContent() == "text");
    REQUIRE(doc.getFilePath().empty());
}

TEST_CASE("Document: пустой контент", "[document]") {

    Document doc(2, "");

    REQUIRE(doc.getContent().empty());
}

TEST_CASE("Document: пустой путь", "[document]") {

    Document doc(3, "hello", "");

    REQUIRE(doc.getFilePath().empty());
}

TEST_CASE("Document: большой текст", "[document]") {

    std::string large(1000, 'a');

    Document doc(4, large);

    REQUIRE(doc.getContent().size() == 1000);
}

TEST_CASE("Document: разные id", "[document]") {

    Document doc1(10, "a");
    Document doc2(20, "b");

    REQUIRE(doc1.getId() != doc2.getId());
}

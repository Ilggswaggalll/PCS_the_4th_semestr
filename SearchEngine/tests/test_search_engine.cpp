#include <catch2/catch_test_macros.hpp>
#include "SearchEngine.h"
#include "InvertedIndex.h"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

TEST_CASE("SearchEngine: exact search", "[engine]") {

    SearchEngine engine;

    InvertedIndex::getInstance().clear();

    fs::create_directories("search");

    std::ofstream("search/test.txt")
        << "hello world";

    engine.loadFolder("search");

    engine.setStrategy(
        std::make_unique<ExactSearchStrategy>()
        );

    auto results = engine.search("hello", 3);

    REQUIRE(results.size() == 1);

    fs::remove_all("search");
}

TEST_CASE("SearchEngine: fuzzy search", "[engine]") {

    SearchEngine engine;

    InvertedIndex::getInstance().clear();

    fs::create_directories("fuzzy");

    std::ofstream("fuzzy/test.txt")
        << "hello";

    engine.loadFolder("fuzzy");

    engine.setStrategy(
        std::make_unique<FuzzySearchStrategy>()
        );

    auto results = engine.search("helo", 1);

    REQUIRE(results.size() == 1);

    fs::remove_all("fuzzy");
}

TEST_CASE("SearchEngine: ничего не найдено", "[engine]") {

    SearchEngine engine;

    InvertedIndex::getInstance().clear();

    fs::create_directories("emptysearch");

    std::ofstream("emptysearch/test.txt")
        << "cat dog";

    engine.loadFolder("emptysearch");

    engine.setStrategy(
        std::make_unique<ExactSearchStrategy>()
        );

    auto results = engine.search("elephant", 1);

    REQUIRE(results.empty());

    fs::remove_all("emptysearch");
}

TEST_CASE("SearchEngine: несколько документов", "[engine]") {

    SearchEngine engine;

    InvertedIndex::getInstance().clear();

    fs::create_directories("docs");

    std::ofstream("docs/a.txt") << "hello";
    std::ofstream("docs/b.txt") << "hello";

    engine.loadFolder("docs");

    engine.setStrategy(
        std::make_unique<ExactSearchStrategy>()
        );

    auto results = engine.search("hello", 1);

    REQUIRE(results.size() == 2);

    fs::remove_all("docs");
}

TEST_CASE("SearchEngine: getDocuments", "[engine]") {

    SearchEngine engine;

    REQUIRE(engine.getDocuments().empty());
}

#include <catch2/catch_test_macros.hpp>
#include "Levenshtein.h"

TEST_CASE("Levenshtein: одинаковые строки", "[levenshtein]") {

    REQUIRE(Levenshtein::distance("hello", "hello") == 0);
}

TEST_CASE("Levenshtein: одна замена", "[levenshtein]") {

    REQUIRE(Levenshtein::distance("cat", "car") == 1);
}

TEST_CASE("Levenshtein: удаление", "[levenshtein]") {

    REQUIRE(Levenshtein::distance("hello", "helo") == 1);
}

TEST_CASE("Levenshtein: вставка", "[levenshtein]") {

    REQUIRE(Levenshtein::distance("cat", "cats") == 1);
}

TEST_CASE("Levenshtein: пустые строки", "[levenshtein]") {

    REQUIRE(Levenshtein::distance("", "") == 0);
}

TEST_CASE("Levenshtein: строка и пустота", "[levenshtein]") {

    REQUIRE(Levenshtein::distance("hello", "") == 5);
}

TEST_CASE("Levenshtein: сложный случай", "[levenshtein]") {

    REQUIRE(Levenshtein::distance("kitten", "sitting") == 3);
}

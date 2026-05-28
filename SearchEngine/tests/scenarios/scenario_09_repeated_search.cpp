#include "test_helper.h"
#include "SearchEngine.h"
#include "InvertedIndex.h"
#include "SearchStrategy.h"

int main() {
    TEST_INFO("Сценарий 9: Повторный поиск");

    TestEnvironment env("scenario_09");
    env.createFile("doc.txt", "first second third");

    SearchEngine engine;
    InvertedIndex::getInstance().clear();
    engine.loadFolder(env.getPath());
    engine.setStrategy(std::make_unique<ExactSearchStrategy>());

    auto first = engine.search("first", 3);
    auto second = engine.search("second", 3);
    auto third = engine.search("third", 3);

    if (!first.empty() && !second.empty() && !third.empty()) {
        TEST_PASS("Повторные поиски работают корректно");
    } else {
        TEST_FAIL("Один из повторных поисков не сработал");
    }

    return 0;
}

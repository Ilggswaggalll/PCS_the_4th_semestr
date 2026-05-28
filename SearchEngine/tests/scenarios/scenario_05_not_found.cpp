#include "test_helper.h"
#include "SearchEngine.h"
#include "InvertedIndex.h"
#include "SearchStrategy.h"

int main() {
    TEST_INFO("Сценарий 5: Поиск отсутствующего слова");

    TestEnvironment env("scenario_05");
    env.createFile("doc.txt", "apple banana cherry");

    SearchEngine engine;
    InvertedIndex::getInstance().clear();
    engine.loadFolder(env.getPath());

    engine.setStrategy(std::make_unique<ExactSearchStrategy>());
    auto results = engine.search("nonexistent", 3);

    if (results.empty()) {
        TEST_PASS("Отсутствующее слово не найдено");
    } else {
        TEST_FAIL("Отсутствующее слово не должно находиться");
    }

    return 0;
}

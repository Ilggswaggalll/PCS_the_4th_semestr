#include "test_helper.h"
#include "SearchEngine.h"
#include "InvertedIndex.h"
#include "SearchStrategy.h"

int main() {
    TEST_INFO("Сценарий 4: Нестрогий поиск с опечаткой");

    TestEnvironment env("scenario_04");
    env.createFile("doc.txt", "hello world");

    SearchEngine engine;
    InvertedIndex::getInstance().clear();
    engine.loadFolder(env.getPath());

    // Нестрогий поиск с опечаткой
    engine.setStrategy(std::make_unique<FuzzySearchStrategy>());
    auto results = engine.search("helo", 2);  // "helo" вместо "hello"

    if (!results.empty()) {
        TEST_PASS("Слово 'helo' найдено как похожее на 'hello'");
    } else {
        TEST_FAIL("Нестрогий поиск не сработал для 'helo'");
    }

    return 0;
}

#include "test_helper.h"
#include "SearchEngine.h"
#include "InvertedIndex.h"
#include "SearchStrategy.h"

int main() {
    TEST_INFO("Сценарий 3: Точный поиск слова");

    TestEnvironment env("scenario_03");
    env.createFile("doc1.txt", "the quick brown fox");
    env.createFile("doc2.txt", "jumps over the lazy dog");
    env.createFile("doc3.txt", "the fox is quick");

    SearchEngine engine;
    InvertedIndex::getInstance().clear();
    engine.loadFolder(env.getPath());

    // Точный поиск
    engine.setStrategy(std::make_unique<ExactSearchStrategy>());
    auto results = engine.search("fox", 3);

    if (results.size() == 2) {
        TEST_PASS("Слово 'fox' найдено в 2 документах");
    } else {
        TEST_FAIL("Ожидалось 2 документа, получено: " + std::to_string(results.size()));
    }

    // Проверяем, что нет ложных срабатываний
    auto notFound = engine.search("nonexistent", 3);
    if (notFound.empty()) {
        TEST_PASS("Несуществующее слово не найдено");
    } else {
        TEST_FAIL("Несуществующее слово не должно находиться");
    }

    return 0;
}

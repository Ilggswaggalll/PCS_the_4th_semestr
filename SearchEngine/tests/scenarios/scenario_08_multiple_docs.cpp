#include "test_helper.h"
#include "SearchEngine.h"
#include "InvertedIndex.h"
#include "SearchStrategy.h"

int main() {
    TEST_INFO("Сценарий 8: Поиск слова в нескольких документах");

    TestEnvironment env("scenario_08");
    env.createFile("doc1.txt", "common word here");
    env.createFile("doc2.txt", "another common word");
    env.createFile("doc3.txt", "no match here");

    SearchEngine engine;
    InvertedIndex::getInstance().clear();
    engine.loadFolder(env.getPath());

    engine.setStrategy(std::make_unique<ExactSearchStrategy>());
    auto results = engine.search("common", 3);

    if (results.size() == 2) {
        TEST_PASS("Слово 'common' найдено в 2 документах");
    } else {
        TEST_FAIL("Ожидалось 2 документа, получено: " + std::to_string(results.size()));
    }

    return 0;
}

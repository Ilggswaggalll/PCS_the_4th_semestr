#include "test_helper.h"
#include "SearchEngine.h"
#include "InvertedIndex.h"
#include "SearchStrategy.h"

int main() {
    TEST_INFO("Сценарий 10: Поиск после повторной индексации");

    // Первая папка
    TestEnvironment env1("scenario_10_1");
    env1.createFile("doc1.txt", "apple");

    // Вторая папка
    TestEnvironment env2("scenario_10_2");
    env2.createFile("doc2.txt", "banana");

    SearchEngine engine;
    InvertedIndex::getInstance().clear();

    // Индексация первой папки
    engine.loadFolder(env1.getPath());
    engine.setStrategy(std::make_unique<ExactSearchStrategy>());
    auto results1 = engine.search("apple", 3);

    if (results1.empty()) {
        TEST_FAIL("Слово 'apple' не найдено после первой индексации");
    }

    // Индексация второй папки
    engine.loadFolder(env2.getPath());
    auto results2 = engine.search("banana", 3);
    auto resultsApple = engine.search("apple", 3);

    if (!results2.empty() && resultsApple.empty()) {
        TEST_PASS("Индекс обновлён, старые данные заменены");
    } else {
        TEST_FAIL("Индекс не обновился корректно");
    }

    return 0;
}

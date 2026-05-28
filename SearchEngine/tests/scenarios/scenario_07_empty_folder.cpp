#include "test_helper.h"
#include "SearchEngine.h"
#include "InvertedIndex.h"

int main() {
    TEST_INFO("Сценарий 7: Индексация пустой папки");

    TestEnvironment env("scenario_07");
    // Не создаём файлов — папка пустая

    SearchEngine engine;
    InvertedIndex::getInstance().clear();

    try {
        engine.loadFolder(env.getPath());
        auto docs = engine.getDocuments();

        if (docs.empty()) {
            TEST_PASS("Пустая папка обработана корректно, документов: 0");
        } else {
            TEST_FAIL("Ожидалось 0 документов, получено: " + std::to_string(docs.size()));
        }
    } catch (const std::exception& e) {
        TEST_FAIL("Ошибка при обработке пустой папки: " + std::string(e.what()));
    }

    return 0;
}

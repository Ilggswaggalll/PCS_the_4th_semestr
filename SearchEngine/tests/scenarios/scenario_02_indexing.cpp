#include "test_helper.h"
#include "SearchEngine.h"
#include "InvertedIndex.h"

int main() {
    TEST_INFO("Сценарий 2: Индексация папки с текстовыми файлами");

    // Создаём тестовую среду
    TestEnvironment env("scenario_02");
    env.createFile("file1.txt", "hello world");
    env.createFile("file2.txt", "goodbye moon");
    env.createFile("file3.txt", "hello again");

    // Индексируем
    SearchEngine engine;
    InvertedIndex::getInstance().clear();

    try {
        engine.loadFolder(env.getPath());
        auto docs = engine.getDocuments();

        if (docs.size() == 3) {
            TEST_PASS("Папка загружена, документов: " + std::to_string(docs.size()));
        } else {
            TEST_FAIL("Ожидалось 3 документа, получено: " + std::to_string(docs.size()));
        }
    } catch (const std::exception& e) {
        TEST_FAIL("Ошибка при индексации: " + std::string(e.what()));
    }

    return 0;
}

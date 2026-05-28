# Находим Catch2 и Qt
find_package(Catch2 REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core)

# Добавляем пути к исходникам
include_directories(${CMAKE_SOURCE_DIR}/include)

# Включаем поддержку Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ========== UNIT-TESTS ==========

# ===== ТЕСТ 1: Levenshtein =====
add_executable(test_levenshtein
    test_levenshtein.cpp
)
target_link_libraries(test_levenshtein PRIVATE Catch2::Catch2WithMain)

# ===== ТЕСТ 2: Document =====
add_executable(test_document
    test_document.cpp
    ${CMAKE_SOURCE_DIR}/src/Document.cpp
)
target_link_libraries(test_document PRIVATE Catch2::Catch2WithMain)

# ===== ТЕСТ 3: InvertedIndex =====
add_executable(test_inverted_index
    test_inverted_index.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertedIndex.cpp
)
target_link_libraries(test_inverted_index PRIVATE Catch2::Catch2WithMain)

# ===== ТЕСТ 4: Indexer =====
add_executable(test_indexer
    test_indexer.cpp
    ${CMAKE_SOURCE_DIR}/src/Indexer.cpp
    ${CMAKE_SOURCE_DIR}/src/Document.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertedIndex.cpp
    ${CMAKE_SOURCE_DIR}/src/DocumentFactory.cpp
)
target_link_libraries(test_indexer PRIVATE Catch2::Catch2WithMain Qt6::Core)

# ===== ТЕСТ 5: SearchEngine =====
add_executable(test_search_engine
    test_search_engine.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/Indexer.cpp
    ${CMAKE_SOURCE_DIR}/src/Document.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertedIndex.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchStrategy.cpp
    ${CMAKE_SOURCE_DIR}/src/DocumentFactory.cpp
)
target_link_libraries(test_search_engine PRIVATE Catch2::Catch2WithMain Qt6::Core)

# ========== СЦЕНАРИИ (мини-программы) ==========

# Вспомогательный хедер для сценариев
set(SCENARIO_HELPER scenarios/test_helper.h)

# Сценарий 1: Запуск программы (заглушка)
add_executable(scenario_01_startup
    scenarios/scenario_01_startup.cpp
)
target_include_directories(scenario_01_startup PRIVATE scenarios)

# Сценарий 2: Индексация папки
add_executable(scenario_02_indexing
    scenarios/scenario_02_indexing.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/Indexer.cpp
    ${CMAKE_SOURCE_DIR}/src/Document.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertedIndex.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchStrategy.cpp
    ${CMAKE_SOURCE_DIR}/src/DocumentFactory.cpp
)
target_link_libraries(scenario_02_indexing PRIVATE Qt6::Core)
target_include_directories(scenario_02_indexing PRIVATE ${CMAKE_SOURCE_DIR}/include scenarios)

# Сценарий 3: Точный поиск
add_executable(scenario_03_exact_search
    scenarios/scenario_03_exact_search.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/Indexer.cpp
    ${CMAKE_SOURCE_DIR}/src/Document.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertedIndex.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchStrategy.cpp
    ${CMAKE_SOURCE_DIR}/src/DocumentFactory.cpp
)
target_link_libraries(scenario_03_exact_search PRIVATE Qt6::Core)
target_include_directories(scenario_03_exact_search PRIVATE ${CMAKE_SOURCE_DIR}/include scenarios)

# Сценарий 4: Нестрогий поиск
add_executable(scenario_04_fuzzy_search
    scenarios/scenario_04_fuzzy_search.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/Indexer.cpp
    ${CMAKE_SOURCE_DIR}/src/Document.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertedIndex.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchStrategy.cpp
    ${CMAKE_SOURCE_DIR}/src/DocumentFactory.cpp
)
target_link_libraries(scenario_04_fuzzy_search PRIVATE Qt6::Core)
target_include_directories(scenario_04_fuzzy_search PRIVATE ${CMAKE_SOURCE_DIR}/include scenarios)

# Сценарий 5: Поиск отсутствующего слова
add_executable(scenario_05_not_found
    scenarios/scenario_05_not_found.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/Indexer.cpp
    ${CMAKE_SOURCE_DIR}/src/Document.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertedIndex.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchStrategy.cpp
    ${CMAKE_SOURCE_DIR}/src/DocumentFactory.cpp
)
target_link_libraries(scenario_05_not_found PRIVATE Qt6::Core)
target_include_directories(scenario_05_not_found PRIVATE ${CMAKE_SOURCE_DIR}/include scenarios)

# Сценарий 6: Пустой запрос (заглушка)
add_executable(scenario_06_empty_query
    scenarios/scenario_06_empty_query.cpp
)
target_include_directories(scenario_06_empty_query PRIVATE scenarios)

# Сценарий 7: Пустая папка
add_executable(scenario_07_empty_folder
    scenarios/scenario_07_empty_folder.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/Indexer.cpp
    ${CMAKE_SOURCE_DIR}/src/Document.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertedIndex.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchStrategy.cpp
    ${CMAKE_SOURCE_DIR}/src/DocumentFactory.cpp
)
target_link_libraries(scenario_07_empty_folder PRIVATE Qt6::Core)
target_include_directories(scenario_07_empty_folder PRIVATE ${CMAKE_SOURCE_DIR}/include scenarios)

# Сценарий 8: Поиск в нескольких документах
add_executable(scenario_08_multiple_docs
    scenarios/scenario_08_multiple_docs.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/Indexer.cpp
    ${CMAKE_SOURCE_DIR}/src/Document.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertedIndex.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchStrategy.cpp
    ${CMAKE_SOURCE_DIR}/src/DocumentFactory.cpp
)
target_link_libraries(scenario_08_multiple_docs PRIVATE Qt6::Core)
target_include_directories(scenario_08_multiple_docs PRIVATE ${CMAKE_SOURCE_DIR}/include scenarios)

# Сценарий 9: Повторный поиск
add_executable(scenario_09_repeated_search
    scenarios/scenario_09_repeated_search.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/Indexer.cpp
    ${CMAKE_SOURCE_DIR}/src/Document.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertedIndex.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchStrategy.cpp
    ${CMAKE_SOURCE_DIR}/src/DocumentFactory.cpp
)
target_link_libraries(scenario_09_repeated_search PRIVATE Qt6::Core)
target_include_directories(scenario_09_repeated_search PRIVATE ${CMAKE_SOURCE_DIR}/include scenarios)

# Сценарий 10: Поиск после переиндексации
add_executable(scenario_10_reindex
    scenarios/scenario_10_reindex.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/Indexer.cpp
    ${CMAKE_SOURCE_DIR}/src/Document.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertedIndex.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchStrategy.cpp
    ${CMAKE_SOURCE_DIR}/src/DocumentFactory.cpp
)
target_link_libraries(scenario_10_reindex PRIVATE Qt6::Core)
target_include_directories(scenario_10_reindex PRIVATE ${CMAKE_SOURCE_DIR}/include scenarios)

# ========== РЕГИСТРАЦИЯ UNIT-ТЕСТОВ ДЛЯ CTest ==========
enable_testing()

add_test(NAME test_levenshtein COMMAND test_levenshtein)
add_test(NAME test_document COMMAND test_document)
add_test(NAME test_inverted_index COMMAND test_inverted_index)
add_test(NAME test_indexer COMMAND test_indexer)
add_test(NAME test_search_engine COMMAND test_search_engine)

# ========== РЕГИСТРАЦИЯ СЦЕНАРИЕВ ДЛЯ CTest ==========
add_test(NAME scenario_01_startup COMMAND scenario_01_startup)
add_test(NAME scenario_02_indexing COMMAND scenario_02_indexing)
add_test(NAME scenario_03_exact_search COMMAND scenario_03_exact_search)
add_test(NAME scenario_04_fuzzy_search COMMAND scenario_04_fuzzy_search)
add_test(NAME scenario_05_not_found COMMAND scenario_05_not_found)
add_test(NAME scenario_06_empty_query COMMAND scenario_06_empty_query)
add_test(NAME scenario_07_empty_folder COMMAND scenario_07_empty_folder)
add_test(NAME scenario_08_multiple_docs COMMAND scenario_08_multiple_docs)
add_test(NAME scenario_09_repeated_search COMMAND scenario_09_repeated_search)
add_test(NAME scenario_10_reindex COMMAND scenario_10_reindex)

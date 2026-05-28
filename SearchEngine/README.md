# Поисковый движок по текстовым файлам

## Описание
Программа реализует простой поисковый движок с использованием **инвертированного индекса**.  
Позволяет индексировать текстовые файлы (формат `.txt`) и выполнять поиск с поддержкой:

- регистронезависимости;
- нечёткого поиска (расстояние Левенштейна до 3 символов);
- ранжирования результатов по релевантности.

## Технологии
- **C++17** — язык программирования;
- **Qt6** — графический интерфейс;
- **Catch2** — unit-тестирование;
- **Docker** — контейнеризация;
- **CMake** — система сборки.

## Структура проекта
```text
SearchEngine/
├── include/ # заголовочные файлы (.h)
│ ├── Document.h
│ ├── Indexer.h
│ ├── InvertedIndex.h
│ ├── SearchEngine.h
│ └── SearchStrategy.h
├── src/ # исходные файлы (.cpp)
├── tests/ # unit-тесты и сценарии
│ ├── test_.cpp # тесты классов
│ └── scenario_.cpp # тестовые сценарии
├── txt_files/ # тестовые текстовые файлы
├── CMakeLists.txt # конфигурация сборки
├── Dockerfile # для контейнеризации
└── README.md

## Сборка проекта

```bash
cmake -S . -B build
cmake --build build

## Запуск
```bash
./build/search_engine

### Запуск тестов
```bash
cd build
ctest --output-on-failure

### Или по отдельности
```bash
./build/tests/test_levenshtein
./build/tests/test_document
./build/tests/test_indexer
./build/tests/test_inverted_index
./build/tests/test_search_engine

## Контейнеризация

## Сборка образа
```bash
docker build -t search-engine .

## Запуск тестов в контейнере
```bash
docker run --rm search-engine /app/tests/test_levenshtein

## Запуск сценариев
```bash
docker run --rm search-engine /app/tests/scenario_02_indexing

## Результаты тестирования
|---|---|
| Тест | Результат |
| test_document	| ✅ 10 assertions |
| test_indexer	✅ 7 assertions |
| test_inverted_index | ✅ 8 assertions |
| test_levenshtein | ✅ 7 assertions |
| test_search_engine | ✅ 5 assertions |

## Паттерны проектирования
Singleton — для инвертированного индекса;

Factory Method — для создания документов;

Strategy — для алгоритмов поиска;

Observer — для обновления индекса;

Facade — для упрощённого интерфейса поиска.

## Автор
Казакбаев Ильгиз Азатович
Группа ЭФБО-01-24
РТУ МИРЭА, 2026 г.
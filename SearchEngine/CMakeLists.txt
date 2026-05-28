cmake_minimum_required(VERSION 3.10)

project(SearchEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

add_executable(search_engine
    src/main.cpp
    src/MainWindow.cpp
    include/MainWindow.h
    include/Document.h
    include/Indexer.h
    include/InvertedIndex.h
    include/SearchEngine.h
    src/SearchEngine.cpp
    src/Document.cpp
    src/Indexer.cpp
    src/InvertedIndex.cpp
    include/Levenshtein.h
    include/SearchStrategy.h
    src/SearchStrategy.cpp
    include/DocumentFactory.h
    src/DocumentFactory.cpp
    include/IndexObserver.h
    src/IndexObserver.cpp
)
target_include_directories(search_engine PRIVATE include)

target_link_libraries(search_engine Qt6::Widgets Qt6::Core)

# Подключаем тесты (если включен флаг BUILD_TESTS)
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt)
    enable_testing()  # <--- ЭТО КЛЮЧЕВАЯ СТРОКА
    add_subdirectory(tests)
endif()

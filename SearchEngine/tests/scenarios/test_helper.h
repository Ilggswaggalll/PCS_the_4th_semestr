#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

// Вывод результата теста
#define TEST_PASS(msg) std::cout << "✅ PASSED: " << msg << std::endl
#define TEST_FAIL(msg) std::cout << "❌ FAILED: " << msg << std::endl
#define TEST_INFO(msg) std::cout << "ℹ️ " << msg << std::endl

// Создание временной папки с тестовыми файлами
class TestEnvironment {
public:
    TestEnvironment(const std::string& name) : testDir(name + "_test") {
        fs::remove_all(testDir);
        fs::create_directories(testDir);
    }

    ~TestEnvironment() {
        fs::remove_all(testDir);
    }

    void createFile(const std::string& filename, const std::string& content) {
        std::ofstream file(testDir + "/" + filename);
        file << content;
        file.close();
    }

    std::string getPath() const { return testDir; }

private:
    std::string testDir;
};

#include "IndexObserver.h"
#include <iostream>

void ConsoleIndexObserver::onIndexUpdated(const std::string& folderPath, int documentCount) {
    std::cout << "[OBSERVER] Индекс обновлён! Папка: " << folderPath
              << ", документов: " << documentCount << std::endl;
}

#pragma once
#include <string>

class IndexObserver {
public:
    virtual ~IndexObserver() = default;
    virtual void onIndexUpdated(const std::string& folderPath, int documentCount) = 0;
};

class ConsoleIndexObserver : public IndexObserver {
public:
    void onIndexUpdated(const std::string& folderPath, int documentCount) override;
};

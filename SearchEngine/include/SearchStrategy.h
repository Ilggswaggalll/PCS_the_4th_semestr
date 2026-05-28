#pragma once
#include <vector>
#include <string>

class SearchStrategy {
public:
    virtual ~SearchStrategy() = default;
    virtual std::vector<int> search(const std::string& query, int maxDistance = 3) = 0;
};

class ExactSearchStrategy : public SearchStrategy {
public:
    std::vector<int> search(const std::string& query, int maxDistance = 3) override;
};

class FuzzySearchStrategy : public SearchStrategy {
public:
    std::vector<int> search(const std::string& query, int maxDistance = 3) override;
};

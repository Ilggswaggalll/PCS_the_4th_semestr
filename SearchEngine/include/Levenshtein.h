#pragma once

#include <string>
#include <algorithm>
#include <vector>

class Levenshtein {

public:

    static int distance(
        const std::string& s1,
        const std::string& s2
        ) {

        size_t len1 = s1.size();
        size_t len2 = s2.size();

        std::vector<std::vector<int>> dp(
            len1 + 1,
            std::vector<int>(len2 + 1)
            );

        for (size_t i = 0; i <= len1; ++i)
            dp[i][0] = static_cast<int>(i);

        for (size_t j = 0; j <= len2; ++j)
            dp[0][j] = static_cast<int>(j);

        for (size_t i = 1; i <= len1; ++i) {

            for (size_t j = 1; j <= len2; ++j) {

                int cost =
                    (s1[i - 1] == s2[j - 1]) ? 0 : 1;

                dp[i][j] = std::min({

                    dp[i - 1][j] + 1,
                        dp[i][j - 1] + 1,
                        dp[i - 1][j - 1] + cost

                });

            }

        }

        return dp[len1][len2];
    }
};

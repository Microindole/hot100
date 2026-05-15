#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 计算将 word1 转换为 word2 所需的最少操作数。
     *
     * 使用动态规划解决。状态转移方程：
     * 1. 若 word1[i-1] == word2[j-1]: dp[i][j] = dp[i-1][j-1]
     * 2. 否则: dp[i][j] = 1 + min({
     *      dp[i-1][j],    // 删除操作：在 word1 中删去当前字符
     *      dp[i][j-1],    // 插入操作：在 word1 中插入 word2 的当前字符
     *      dp[i-1][j-1]   // 替换操作：将 word1 字符替换为 word2 字符
     *    })
     *
     * @param word1 源字符串
     * @param word2 目标字符串
     * @return int 最小编辑步数
     */
    int minDistance(string word1, string word2) {
        int len1 = word1.size(), len2 = word2.size();

        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, INT_MAX));

        dp[0][0] = 0;

        for (int i = 1; i <= len1; i++) dp[i][0] = i;

        for (int i = 1; i <= len2; i++) dp[0][i] = i;

        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }

                else {
                    dp[i][j] =
                        1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                }
            }
        }

        return dp[len1][len2];
    }
};
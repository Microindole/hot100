#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.size(), len2 = word2.size();

        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, INT_MAX));
        dp[0][0] = 0;

        for (int i = 1; i <= len1; i++) {
            dp[i][0] = i;
        }
        for (int i = 1; i <= len2; i++) {
            dp[0][i] = i;
        }

        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1],
                                dp[i][j]}) +
                           1;

                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
                }
            }
        }

        return dp[len1][len2];
    }
};

// 因为只需要该行和前一行，所以可以用一维滚动数组来节省空间
class Solution2 {
public:
    int minDistance(string word1, string word2) {
        if (word1.size() < word2.size()) {
            swap(word1, word2);
        }

        int m = word1.size();
        int n = word2.size();

        vector<int> dp(n + 1);

        for (int j = 0; j <= n; j++) {
            dp[j] = j;
        }

        for (int i = 1; i <= m; i++) {
            int prev = dp[0];
            dp[0] = i;

            for (int j = 1; j <= n; j++) {
                int temp = dp[j];

                if (word1[i - 1] == word2[j - 1]) {
                    dp[j] = prev;
                } else {
                    dp[j] = min({
                                dp[j],      // 上方：dp[i-1][j]
                                dp[j - 1],  // 左边：dp[i][j-1]
                                prev        // 左上：dp[i-1][j-1]
                            }) +
                            1;
                }

                prev = temp;
            }
        }

        return dp[n];
    }
};
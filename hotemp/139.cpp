#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> thisset(wordDict.begin(), wordDict.end());
        int n = s.size();

        vector<bool> dp(n + 1, false);
        dp[0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && thisset.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }

    /**
     * 这里可以根据最长单词确认遍历范围优化一下
     *
     * int maxLen = 0;
     * for (const string& word : wordDict) {
     *     maxLen = max(maxLen, (int)word.length());
     * }
     *
     * for (int i = 1; i <= n; i++) {
     *     // j 不再从 0 开始，而是从 i 减去最大长度开始
     *     for (int j = i - 1; j >= 0 && i - j <= maxLen; j--) {
     *         if (dp[j] && thisset.count(s.substr(j, i - j))) {
     *             dp[i] = true;
     *             break;
     *         }
     *     }
     * }
     */
};
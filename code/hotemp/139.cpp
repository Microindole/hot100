#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());

        unordered_set<int> lenSet;
        for (const string& word : wordDict) {
            lenSet.insert(word.size());
        }

        vector<int> lengths(lenSet.begin(), lenSet.end());
        sort(lengths.begin(), lengths.end());

        int n = s.size();
        vector<bool> dp(n + 1, false);
        dp[0] = true;

        for (int i = 1; i <= n; i++) {
            for (int len : lengths) {
                if (len > i) {
                    break;
                }

                int j = i - len;

                if (dp[j] && wordSet.count(s.substr(j, len))) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};
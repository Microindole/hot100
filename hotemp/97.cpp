#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int len1 = s1.size(), len2 = s2.size(), len3 = s3.size();

        if (len3 != len1 + len2)
            return false;

        vector<vector<bool>> dp(len1 + 1, vector<bool>(len2 + 1, false));
        dp[0][0] = true;

        for (int i = 0; i < len1 + 1; i++) {
            for (int j = 0; j < len2 + 1; j++) {
                int p = i + j - 1;

                if (i > 0)
                    dp[i][j] = dp[i][j] || dp[i - 1][j] && s1[i - 1] == s3[p];

                if (j > 0)
                    dp[i][j] = dp[i][j] || dp[i][j - 1] && s2[j - 1] == s3[p];
            }
        }

        return dp[len1][len2];
    }
};
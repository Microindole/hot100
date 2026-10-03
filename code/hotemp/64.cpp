#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        vector<int> dp(m, INT_MAX);
        dp[0] = grid[0][0];

        for (int i = 1; i < m; i++) {
            dp[i] = dp[i - 1] + grid[0][i];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j == 0) {
                    dp[j] = dp[0] + grid[i][j];
                } else {
                    dp[j] = min(dp[j - 1], dp[j]) + grid[i][j];
                }
            }
        }

        return dp[m - 1];
    }
};
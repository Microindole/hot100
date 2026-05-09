#include <vector>

using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> points(n + 2, 1);
        for (int i = 0; i < n; i++) points[i + 1] = nums[i];

        // dp[i][j] 表示戳破 (i, j) 间所有气球的最大得分
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

        // 从下往上，从左往右遍历（保证子区间先算好）
        for (int i = n; i >= 0; i--) {
            for (int j = i + 2; j <= n + 1; j++) {
                // k 是 (i, j) 之间最后一个被戳破的气球
                for (int k = i + 1; k < j; k++) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + points[i] * points[k] * points[j]);
                }
            }
        }
        return dp[0][n + 1];
    }
};
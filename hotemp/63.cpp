#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * uniquePathsWithObstacles - 使用滚动数组优化空间的 LIS 解法
 * @obstacleGrid: 障碍物网格
 * * 空间优化原理：
 * 我们只关心当前行和上一行的状态。在一维数组 dp[j] 中：
 * - 更新前的 dp[j] 实际上存储的是上一行同一列的值 dp[i-1][j]。
 * - 更新后的 dp[j-1] 存储的是当前行左侧的值 dp[i][j-1]。
 */
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        vector<long long> dp(n, 0);

        dp[0] = (obstacleGrid[0][0] == 0);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0;
                    continue;
                }

                if (j > 0 && obstacleGrid[i][j] == 0) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return (int)dp[n - 1];
    }
};
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 最多完成两次交易。
     *
     * 状态机图解 (State Machine):
     * [0] 无操作 -> [1] 第一次持有 -> [2] 第一次卖出
     *                |                ^
     *                |                |
     *                +--> [3] 第二次持有 -> [4] 第二次卖出
     *
     * 转移逻辑：
     * dp[1]: max(前天持有, -今天价格)
     * dp[2]: max(前天卖出, 前天持有 + 今天价格)
     * ... 以此类推
     */
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        vector<int> dp(5, -1e9);

        for (int i = 0; i < n; i++) {
            dp[0] = 0;
            dp[1] = max(-prices[i], dp[1]);
            dp[2] = max(prices[i] + dp[1], dp[2]);
            dp[3] = max(dp[2] - prices[i], dp[3]);
            dp[4] = max(dp[3] + prices[i], dp[4]);
        }

        return dp[4];
    }
};
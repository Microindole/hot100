#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 使用 dp[2k+1] 解决 k 次交易问题
     *
     * 状态说明：
     * j 为奇数 (1, 3, ...): 第 (j+1)/2 次买入
     * j 为偶数 (2, 4, ...): 第 j/2 次卖出
     */
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty() || k == 0)
            return 0;
        int n = prices.size();

        vector<int> dp(2 * k + 1, 0);

        for (int j = 1; j <= 2 * k; j += 2) {
            dp[j] = -prices[0];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= 2 * k; j += 2) {
                dp[j] = max(dp[j], dp[j - 1] - prices[i]);
                dp[j + 1] = max(dp[j + 1], dp[j] + prices[i]);
            }
        }

        return dp[2 * k];
    }
};
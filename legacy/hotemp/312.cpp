#include <vector>

using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();

        vector<int> arr(n + 2);
        arr[0] = arr[n + 1] = 1;

        for (int i = 0; i < n; i++) {
            arr[i + 1] = nums[i];
        }

        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

        for (int len = 2; len <= n + 1; len++) {
            for (int i = 0; i + len <= n + 1; i++) {
                int j = i + len;

                for (int k = i + 1; k < j; k++) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] +
                                                 arr[i] * arr[k] * arr[j]);
                }
            }
        }

        return dp[0][n + 1];
    }
};
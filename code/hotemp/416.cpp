#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int i : nums) sum += i;

        if (sum % 2 != 0)
            return false;

        int target = sum / 2;

        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int i : nums) {
            for (int j = target; j >= i; j--) {
                dp[j] = dp[j] || dp[j - i];
            }
        }

        return dp[target];
    }
};
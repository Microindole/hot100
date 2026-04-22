#include <vector>

using namespace std;

int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) {
        return nums[0];
    }

    int dp1 = max(nums[0], nums[1]);

    if (n == 2) {
        return dp1;
    }

    int dp, dp2 = nums[0];
    for (int i = 2; i < n; i++) {
        dp = max(dp1, dp2 + nums[i]);
        dp2 = dp1;
        dp1 = dp;
    }

    return dp;
}
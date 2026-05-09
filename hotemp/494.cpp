#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    // int findTargetSumWays(vector<int>& nums, int target) {
    //     int count = 0;

    //     getCount(nums, target, 0, 0, count);

    //     return count;
    // }

    // void getCount(vector<int>& nums, int target, int index, int sum,
    //               int& count) {
    //     if (index == nums.size()) {
    //         if (sum == target) {
    //             count++;
    //         }
    //     } else {
    //         getCount(nums, target, index + 1, sum + nums[index], count);
    //         getCount(nums, target, index + 1, sum - nums[index], count);
    //     }
    // }

    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;

        for (int x : nums) {
            sum += x;
        }

        if (abs(target) > sum || (sum + target) % 2 != 0) {
            return 0;
        }

        int bagSize = (sum + target) / 2;

        vector<int> dp(bagSize + 1, 0);
        dp[0] = 1;

        for (int x : nums) {
            for (int j = bagSize; j >= x; j--) {
                dp[j] += dp[j - x];
            }
        }

        return dp[bagSize];
    }
};
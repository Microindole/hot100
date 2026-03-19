#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int now = nums[0];
        int res = now;

        for (int i = 1; i < nums.size(); i++) {
            now = max(nums[i], now + nums[i]);
            res = max(res, now);
        }

        return res;
    }
};
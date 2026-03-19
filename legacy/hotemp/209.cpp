#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        if (n == 0)
            return 0;

        int minLength = INT_MAX;
        int sum = 0;
        int left = 0;

        for (int right = 0; right < n; right++) {
            sum += nums[right];

            // 当当前和大于等于目标值时，尝试收缩左边界以寻找更短的长度
            while (sum >= target) {
                minLength = min(minLength, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }

        return minLength == INT_MAX ? 0 : minLength;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    vector<int> nums = {2, 3, 1, 2, 4, 3};
    int target = 7;

    cout << sol.minSubArrayLen(target, nums) << endl;

    return 0;
}
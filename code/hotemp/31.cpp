#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int index = -1;

        // 找最右边的 nums[i] < nums[i + 1]
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            // 必须从右向左找第一个 > nums[index] 的数
            int j = n - 1;

            while (nums[j] <= nums[index]) {
                j--;
            }

            swap(nums[index], nums[j]);
        }

        reverse(nums.begin() + index + 1, nums.end());
    }
};
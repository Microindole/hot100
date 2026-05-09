#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();

        int index = -1;

        for (int i = n - 1; i > 0; i--) {
            if (nums[i - 1] < nums[i]) {
                index = i - 1;
                break;
            }
        }

        if (index == -1) {
            sort(nums.begin(), nums.end());
        } else {
            int minmax = INT_MAX;
            int minmaxIndex = -1;
            for (int i = index; i < n; i++) {
                if (nums[i] > nums[index] && nums[i] < minmax) {
                    minmax = nums[i];
                    minmaxIndex = i;
                }
            }

            swap(nums[index], nums[minmaxIndex]);
            sort(nums.begin() + index + 1, nums.end());
        }
    }
};
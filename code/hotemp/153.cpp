#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int getK(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;

        if (nums.size() <= 1 || nums[left] < nums[right]) {
            return -1;
        }

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid + 1] < nums[mid]) {
                return mid;
            }

            if (nums[mid] < nums[left]) {
                right = mid;
            } else {
                left = mid;
            }
        }

        return -1;
    }
    int findMin(vector<int>& nums) { return nums[getK(nums) + 1]; }
};
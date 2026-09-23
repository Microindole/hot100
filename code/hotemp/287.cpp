#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            int tempi = i;
            while (nums[tempi] != tempi + 1) {
                int temp = nums[nums[tempi] - 1];
                nums[nums[tempi] - 1] = nums[tempi];
                tempi = temp;
            }
        }

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i + 1) {
                return nums[i];
            }
        }

        return -1;
    }
};
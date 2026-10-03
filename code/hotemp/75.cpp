#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int one = 0;
        int zero = 0;

        for (int i : nums) {
            if (i == 1) {
                one++;
            } else if (i == 0) {
                zero++;
            }
        }

        for (int i = 0; i < nums.size(); i++) {
            if (i < zero) {
                nums[i] = 0;
            } else if (i < zero + one && i >= zero) {
                nums[i] = 1;
            } else {
                nums[i] = 2;
            }
        }
    }
};
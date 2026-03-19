#include <vector>

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int slow = 0;

        for (int fast = 0; fast < nums.size(); fast++) {
            if (nums[fast]) {
                nums[slow++] = nums[fast];
            }
        }

        for (int i = slow; i < nums.size(); i++) {
            nums[i] = 0;
        }
    }
};
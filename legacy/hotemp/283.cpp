#include <vector>

using namespace std;

void moveZeroes(vector<int>& nums) {
    int slow = 0;
    // 阶段一：只管把非零的拿过来
    for (int fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != 0) {
            nums[slow++] = nums[fast];
        }
    }
    // 阶段二：后面的全变 0
    for (int i = slow; i < nums.size(); i++) {
        nums[i] = 0;
    }
}
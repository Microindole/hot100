#include <vector>

using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // 1. 寻找相遇点（确定有环）
        int slow = nums[0];
        int fast = nums[nums[0]];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }

        // 2. 寻找环的入口（即重复数字）
        int pre1 = 0;
        int pre2 = slow;
        while (pre1 != pre2) {
            pre1 = nums[pre1];
            pre2 = nums[pre2];
        }
        return pre1;
    }
};
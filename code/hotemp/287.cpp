#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0];
        int fast = nums[nums[0]];

        while (fast != slow) {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }

        int p2 = nums[0];
        int p1 = nums[slow];
        while (p1 != p2) {
            p1 = nums[p1];
            p2 = nums[p2];
        }

        return p1;
    }
};
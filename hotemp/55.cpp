#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();

        int maxJump = 0;
        for (int i = 0; i <= (maxJump < n - 1 ? maxJump : n - 1); i++) {
            if (i + nums[i] > maxJump) {
                maxJump = i + nums[i];
            }
        }

        return maxJump >= n - 1;
    }
};

void coutCan(bool bl) {
    if (bl) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
}

int main() {
    vector<int> nums1 = {2, 3, 1, 1, 4}, nums2 = {3, 2, 1, 0, 4};

    Solution sol;
    coutCan(sol.canJump(nums1));
    coutCan(sol.canJump(nums2));
}
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int dis = 0;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if (i > dis) {
                return false;
            }

            dis = max(dis, i + nums[i]);

            if (dis >= n - 1) {
                return true;
            }
        }

        return true;
    }
};
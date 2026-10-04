#include <vector>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return 0;
        }

        int maxReach = 0, nowReach = 0, step = 0;

        for (int i = 0; i < n - 1; i++) {
            maxReach = max(maxReach, i + nums[i]);

            if (i == nowReach) {
                step++;
                nowReach = maxReach;

                if (maxReach >= n - 1) {
                    return step;
                }
            }
        }

        return step;
    }
};
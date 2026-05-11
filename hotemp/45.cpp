#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        int steps = 0;
        int current_end = 0;
        int max_reach = 0;

        for (int i = 0; i < n - 1; i++) {
            max_reach = max(max_reach, i + nums[i]);

            if (i == current_end) {
                steps++;
                current_end = max_reach;

                if (current_end >= n - 1) break;
            }
        }
        return steps;
    }
};
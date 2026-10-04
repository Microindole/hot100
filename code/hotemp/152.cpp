#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int currMax = nums[0], currMin = nums[0];
        int resMax = currMax;

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < 0)
                swap(currMax, currMin);

            currMax = max(nums[i], nums[i] * currMax);
            currMin = min(nums[i], nums[i] * currMin);

            resMax = max(resMax, currMax);
        }

        return resMax;
    }
};

int main() {
    vector<int> nums = {-2, 3, -4};

    Solution sol;
    cout << sol.maxProduct(nums) << endl;
}

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> umap;

        for (int i = 0; i < nums.size(); i++) {
            umap[nums[i]] = i;
        }

        for (int i = 0; i < nums.size(); i++) {
            int temp = target - nums[i];

            if (umap.count(temp) && umap[temp] != i) {
                return {i, umap[temp]};
            }
        }

        return {-1, -1};
    }
};

int main() {
    Solution sol;

    int target = 6;
    vector<int> nums = {1, 3, 3, 4};

    vector<int> res = sol.twoSum(nums, target);

    return 0;
}
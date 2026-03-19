#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> show;

        int n = nums.size();
        for (int i = 0; i < n; i++) {
            show[nums[i]] = i;
        }

        for (int i = 0; i < n; i++) {
            int temp = target - nums[i];
            if (show.count(temp) && show[temp] != i) {
                return {i, show[temp]};
            }
        }

        return {-1, -1};
    }
};

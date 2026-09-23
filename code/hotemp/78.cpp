#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();

        vector<int> thisVector;

        vector<vector<int>> res;

        dfs(nums, res, thisVector, n, 0);

        return res;
    }

    void dfs(vector<int>& nums, vector<vector<int>>& res,
             vector<int>& thisVector, int& n, int index) {
        if (index == n) {
            res.push_back(thisVector);
            return;
        }

        for (int i = 0; i < 2; i++) {
            if (i) {
                thisVector.push_back(nums[index]);
                dfs(nums, res, thisVector, n, index + 1);
                thisVector.pop_back();
            } else {
                dfs(nums, res, thisVector, n, index + 1);
            }
        }
    }
};
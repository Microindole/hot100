#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;

        vector<int> thisVector;

        int n = nums.size();

        vector<bool> used(n, false);

        dfs(nums, res, thisVector, n, used);

        return res;
    }

    void dfs(vector<int>& nums, vector<vector<int>>& res,
             vector<int>& thisVector, int& n, vector<bool>& used) {
        if (thisVector.size() == n) {
            res.push_back(thisVector);
            return;
        }

        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                used[i] = true;

                thisVector.push_back(nums[i]);

                dfs(nums, res, thisVector, n, used);

                thisVector.pop_back();

                used[i] = false;
            }
        }
    }
};

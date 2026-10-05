#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    void dfs(vector<int>& candidates, int target, vector<vector<int>>& res,
             vector<int>& path, int now, int start) {
        if (now == target) {
            res.push_back(path);
            return;
        }

        if (now > target)
            return;

        for (int i = start; i < candidates.size(); i++) {
            if (candidates[i] > target)
                break;

            path.push_back(candidates[i]);
            dfs(candidates, target, res, path, now + candidates[i], i);
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        sort(candidates.begin(), candidates.end());
        vector<int> path;

        dfs(candidates, target, res, path, 0, 0);

        return res;
    }
};
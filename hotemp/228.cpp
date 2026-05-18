#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        int n = nums.size();

        if (n == 0)
            return res;

        for (int i = 0; i < n; i++) {
            int start = i;

            while (i + 1 < n && nums[i + 1] == nums[i] + 1) {
                i++;
            }

            if (start == i) {
                res.push_back(to_string(nums[start]));
            } else {
                res.push_back(to_string(nums[start]) + "->" +
                              to_string(nums[i]));
            }
        }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    vector<int> nums = {0, 2, 3, 4, 6, 8, 9};

    vector<string> res = sol.summaryRanges(nums);
    for (string s : res) {
        cout << s << " ";
    }

    return 0;
}
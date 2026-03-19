#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;

        int n = intervals.size();

        if (n == 0) {
            return res;
        }

        sort(intervals.begin(), intervals.end(),
             [](const auto& a, const auto& b) {
                 if (a[0] == b[0]) {
                     return a[1] < b[1];
                 }

                 return a[0] < b[0];
             });

        for (int i = 0; i < intervals.size(); i++) {
            int start = intervals[i][0];

            int end = intervals[i][1];

            while (i < intervals.size() - 1 && end >= intervals[i + 1][0]) {
                end = max(end, intervals[i + 1][1]);
                i++;
            }

            res.push_back({start, end});
        }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};

    vector<vector<int>> res = sol.merge(intervals);

    for (const auto& arr : res) {
        cout << "[" << arr[0] << ", " << arr[1] << "]" << " ";
    }

    return 0;
}
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;

        sort(intervals.begin(), intervals.end(),
             [](const auto& a, const auto& b) {
                 if (a[0] == b[0]) {
                     return a[1] < b[1];
                 }
                 return a[0] < b[0];
             });

        for (int i = 0; i < intervals.size(); i++) {
            int start = intervals[i][0], end = intervals[i][1];

            while (i < intervals.size() - 1 && end >= intervals[i + 1][0]) {
                end = max(intervals[i + 1][1], end);
                i++;
            }

            res.push_back({start, end});
        }

        return res;
    }
};
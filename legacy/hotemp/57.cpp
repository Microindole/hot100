#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 将新区间插入到一组已排序且不重叠的区间中，并合并所有重叠区间。
     *
     * 算法核心通过单次遍历处理，区间关系图示如下：
     *
     * 1. 新区间在当前区间右侧（无重叠）：
     *    intervals[i]: [ start---end ]
     *    newInterval:                  [ newStart---newEnd ]
     *    操作：直接将 intervals[i] 放入结果，继续遍历。
     *
     * 2. 新区间在当前区间左侧（无重叠）：
     *    intervals[i]:                 [ start---end ]
     *    newInterval:  [ newStart---newEnd ]
     *    操作：先放 newInterval，再放 intervals[i]，标记 finish = true。
     *
     * 3. 区间重叠（合并边界）：
     *    intervals[i]:    [ start-------end ]
     *    newInterval:          [ newStart-------newEnd ]
     *    合并后:          [ min(start,ns)---max(end,ne) ]
     *    操作：利用 while 循环持续向后吞并重叠区间，更新并扩展 end 边界。
     *
     * @param intervals 已经按起点升序排列的区间列表
     * @param newInterval 准备插入的新区间 [newStart, newEnd]
     * @return vector<vector<int>> 合并完成后的全新区间列表
     *
     * @complexity
     * - 时间复杂度: O(N) - 仅需单次循环遍历整个区间数组。
     * - 空间复杂度: O(1) - 除返回值外，仅消耗常数级别的迭代变量空间。
     */
    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {
        bool finish = false;
        vector<vector<int>> res;
        int n = intervals.size();

        for (int i = 0; i < intervals.size(); i++) {
            int start = intervals[i][0];
            int end = intervals[i][1];

            if (finish) {
                res.push_back(intervals[i]);
                continue;
            }

            // 情况 2：新区间完全在当前区间前面
            if (newInterval[1] < start) {
                res.push_back(newInterval);
                res.push_back(intervals[i]);
                finish = true;
                continue;
            }

            // 情况 1：新区间完全在当前区间后面
            if (newInterval[0] > end) {
                res.push_back(intervals[i]);
                continue;
            }

            // 情况 3：区间重叠，开始合并
            start = min(start, newInterval[0]);
            end = max(end, newInterval[1]);

            while (i < n && newInterval[1] >= intervals[i][0]) {
                end = max(intervals[i][1], end);
                i++;
                finish = true;
            }
            i--;  // 抵消 for 循环的 i++，防止跳过元素

            res.push_back({start, end});
        }

        // 兜底：如果新区间比所有区间都大，或者 intervals 为空
        if (!finish) {
            res.push_back(newInterval);
        }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    vector<vector<int>> intervals = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    vector<int> newInterval = {4, 8};

    vector<vector<int>> res = sol.insert(intervals, newInterval);

    for (const auto& arr : res) {
        cout << "[" << arr[0] << ", " << arr[1] << "]" << " ";
    }

    return 0;
}
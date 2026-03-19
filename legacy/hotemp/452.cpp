#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 计算引爆所有气球所需的最小弓箭数。
     *
     * 算法采用贪心策略：将所有气球按右端点（结束坐标）升序排序，
     * 优先照顾最先结束的气球。每一根箭都精准射在当前未引爆气球的
     * 右端点上，从而使单根箭向右延伸的覆盖容纳度达到最大。
     *
     * 气球重叠与射箭逻辑图示：
     *
     * 1. 初始化：第一根箭射在排序后第一个气球的右端点：
     *    气球 1:  [ start1 ----------- end1 ]
     *    箭位置:                        ↑ (current_end = end1)
     *
     * 2. 遍历后续气球进行贪心决策：
     *
     *    情况 A (有交集，可顺便引爆)：
     *    气球 2:       [ start2 ----------- end2 ]  (start2 <= current_end)
     *    箭位置:                        ↑
     *    结果  : 被当前箭顺便引爆，箭数不增加。
     *
     *    情况 B (无交集，无法引爆)：
     *    气球 3:                               [ start3 ------- end3 ]
     *    箭位置:                        ↑ (够不着! start3 > current_end)
     *    结果  : 必须射出新箭，更新 current_end = end3，arrows++。
     *
     * @param points 二维数组，每个元素表示气球的 X 轴区间 [start, end]
     * @return int 引爆所有气球所需的最少弓箭数量
     *
     * @complexity
     * - 时间复杂度: O(N log N) - 耗时核心在于对气球右端点进行标准排序。
     * - 空间复杂度: O(1) - 仅使用常数级别的额外指针变量。
     */
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty())
            return 0;

        sort(points.begin(), points.end(),
             [](const auto& a, const auto& b) { return a[1] < b[1]; });

        int arrows = 1;
        int current_end = points[0][1];

        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > current_end) {
                arrows++;

                current_end = points[i][1];
            }
        }

        return arrows;
    }
};
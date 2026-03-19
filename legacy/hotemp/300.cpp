#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * lengthOfLIS - 计算最长递增子序列的长度
     * @nums: 输入的整数数组
     *
     * 算法原理：贪心 + 二分查找
     * 复杂度：时间 O(n log n)，空间 O(n)
     *
     * 逻辑示意图：
     * 数组 tails[i] 表示长度为 i+1 的所有递增子序列中，最小的末尾数值。
     * * 扫描过程示例 [10, 9, 2, 5, 3]:
     * 1. x = 10: [10]          (新建堆)
     * 2. x = 9:  [9]           (9 比 10 小，替换 10，序列潜力更好)
     * 3. x = 2:  [2]           (2 比 9 小，替换 9)
     * 4. x = 5:  [2, 5]        (5 比 2 大，新建堆，当前最长为 2)
     * 5. x = 3:  [2, 3]        (3 找到第一个 >= 它的位置 5，替换之)
     *
     * 最终 tails 的长度即为结果。
     */
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty())
            return 0;

        vector<int> tails;

        for (int x : nums) {
            int left = 0;
            int right = tails.size();

            while (left < right) {
                int mid = left + (right - left) / 2;
                if (tails[mid] < x) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }

            if (left == tails.size()) {
                tails.push_back(x);
            } else {
                tails[left] = x;
            }
        }

        // tails 的长度就是最长递增子序列的长度
        return tails.size();
    }
    /**
     * 以下是经典的动态规划的解法，更易于理解，但是时间复杂度为 O(n^2)
     *
     * int lengthOfLIS(vector<int>& nums) {
     *     int n = nums.size();
     *     if (n == 0) return 0;
     *
     *     // 初始化 dp 数组，每个位置初始长度至少为 1（即它自己）
     *     vector<int> dp(n, 1);
     *     int res = 1;
     *
     *     for (int i = 1; i < n; i++) {
     *         for (int j = 0; j < i; j++) {
     *             if (nums[i] > nums[j]) {
     *                 // 状态转移方程
     *                 dp[i] = max(dp[i], dp[j] + 1);
     *             }
     *         }
     *         res = max(res, dp[i]); // 更新全局最大长度
     *     }
     *     return res;
     * }
     */
};
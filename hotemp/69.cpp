#include <algorithm>

class Solution {
public:
    int mySqrt(int x) { return 0; }

    /**
     * @brief 线性搜索法
     *
     * 时间复杂度: O(sqrt(x))
     * 空间复杂度: O(1)
     *
     * 逻辑：从 1 开始累加，直到找到第一个平方后大于 x 的数。
     */
    int mySqrtLinear(int x) {
        if (x < 2)
            return x;
        // 使用 long long 防止 i++ 时可能出现的边界情况，
        // 或直接用 i <= x / i 约束
        for (int i = 1; i <= x; i++) {
            if (i > x / i)
                return i - 1;
            if (i == x / i)
                return i;
        }
        return 0;
    }

    /**
     * @brief 二分查找法
     *
     * 时间复杂度: O(log x)
     * 空间复杂度: O(1)
     *
     * 逻辑：在 [1, x/2] 范围内二分。若 mid^2 <= x，则 mid 可能是答案，
     * 继续在右半部分找更大的；若 mid^2 > x，则在左半部分找。
     */
    int mySqrtBinary(int x) {
        if (x < 2)
            return x;

        int left = 1, right = x / 2;
        int ans = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            // 使用除法判断 mid * mid <= x，防止溢出
            if (mid <= x / mid) {
                ans = mid;       // 记录当前可能的解
                left = mid + 1;  // 尝试更大的整数
            } else {
                right = mid - 1;
            }
        }
        return ans;
    }

    /**
     * @brief 牛顿迭代法
     *
     * 时间复杂度: O(log log x) - 极快收敛
     * 空间复杂度: O(1)
     *
     * 逻辑：从 x 开始迭代，不断利用切线逼近零点。
     * 对于整数平方根，当相邻两次迭代结果的整数部分相同时停止。
     */
    int mySqrtNewton(int x) {
        if (x < 2)
            return x;

        double x0 = x;
        double C = x;
        while (true) {
            double xi = 0.5 * (x0 + C / x0);
            // 如果两次迭代结果非常接近，说明已经收敛到整数解范围
            if (abs(x0 - xi) < 1e-7)
                break;
            x0 = xi;
        }
        return (int)x0;
    }
};
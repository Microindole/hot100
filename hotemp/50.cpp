#include <iostream>

class Solution {
public:
    /**
     * @brief 递归实现快速幂。
     *
     * 逻辑：
     * 1. 基础情况：x^0 = 1。
     * 2. 递归：先算出 half = x^(n/2)。
     * 3. 合并：结果 = half * half。如果是奇数，再多乘一个 x。
     *
     * 时间复杂度: O(log n)
     * 空间复杂度: O(log n) - 递归深度
     */
    double myPow(double x, int n) {
        long long N = n;  // 防止 -INT_MIN 溢出
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        return fastPow(x, N);
    }

private:
    double fastPow(double x, long long n) {
        if (n == 0)
            return 1.0;

        // 关键：只计算一次递归，避免退化成 O(n)
        double half = fastPow(x, n / 2);

        if (n % 2 == 0) {
            return half * half;
        } else {
            return half * half * x;
        }
    }
};
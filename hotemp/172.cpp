class Solution {
public:
    /**
     * @brief 计算 n! 结尾零的个数。
     *
     * 逻辑图解：
     * n = 100:
     * 1. 100/5  = 20 -> 含有因子 5 的数有 20 个
     * 2. 100/25 = 4  -> 含有因子 25 的数有 4 个 (额外多贡献一个 5)
     * 3. 100/125 = 0 -> 停止
     * 总数 = 20 + 4 = 24
     */
    int trailingZeroes(int n) {
        int count = 0;
        while (n >= 5) {
            // 每次除以 5，相当于计算当前范围内 5, 25, 125... 的倍数个数
            count += n / 5;
            n /= 5;
        }
        return count;
    }
};
#include <cstdint>

class Solution {
public:
    /**
     * @brief 颠倒给定的 32 位无符号整数的二进制位。
     *
     * 算法采用位运算法：循环 32 次，每次将结果 res 左移一位腾出空位，
     * 然后通过 n & 1 取出 n 的最低位拼接到 res 的末尾，最后将 n 右移一位。
     *
     * 二进制位颠倒动态图示 (以 4 位整数演示从 n 传送到 res 的过程)：
     *
     *   初始状态:  n = 1011 ,  res = 0000
     *
     *   Step 1 :  取出 n 最低位 '1' -> 放入 res 末尾 -> res=0001, n右移变为101
     *   Step 2 :  res左移变为0010  -> 放入 n 最低位 '1' -> res=0011,
     * n右移变为10 Step 3 :  res左移变为0110  -> 放入 n 最低位 '0' -> res=0110,
     * n右移变为1 Step 4 :  res左移变为1100  -> 放入 n 最低位 '1' -> res=1101,
     * n右移变为0
     *
     *   最终结果: res = 1101 (完美实现 1011 的前后颠倒)
     *
     * @param n 32位无符号整数
     * @return uint32_t 颠倒二进制位后的 32 位无符号整数
     *
     * @complexity
     * - 时间复杂度: O(1) - 循环次数固定为 32 次，执行时间为常数级。
     * - 空间复杂度: O(1) - 仅使用了一个常数级别的辅助变量 res。
     */
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;

        for (int i = 0; i < 32; i++) {
            res = (res << 1) | (n & 1);

            n >>= 1;
        }

        return res;
    }
};
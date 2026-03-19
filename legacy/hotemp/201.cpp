
class Solution1 {
public:
    /**
     * @brief 解法一：位移法 (寻找公共二进制前缀)
     *
     * 算法核心：由于区间内数字连续递增，低位会不断在 0 和 1 之间翻转。
     * 在按位与 (&) 运算中，任何位只要经历过 0，最终结果该位必为 0。
     * 因此，区间内所有数字按位与的结果，本质上就是 left 和 right 的
     * “公共二进制前缀”，而不同的低位部分则需要全部抹平为 0。
     *
     * 位移法找公共前缀图示 (例如 left = 9, right = 12)：
     *
     *   循环移动前:               同步向右移位(寻找相等点):
     *   left  : 1 0 0 1 (9)       Step 1: 100(4) != 110(6)  [shift=1]
     *   right : 1 1 0 0 (12)      Step 2: 10(2)  == 10(2)   [shift=2]
     *
     *   找到公共前缀 "10"，最后向左移回原位补 0:
     *   结果  : 1 0 0 0 (8)
     *
     * @param left 区间左边界 (闭区间)
     * @param right 区间右边界 (闭区间)
     * @return int 区间内所有数字按位与的结果
     *
     * @complexity
     * - 时间复杂度: O(1) - 32位整型数，while 循环最多执行 32 次。
     * - 空间复杂度: O(1) - 仅使用一个常数级别的辅助变量 shift。
     */
    int rangeBitwiseAnd(int left, int right) {
        int shift = 0;

        while (left < right) {
            left >>= 1;
            right >>= 1;

            shift++;
        }

        return left << shift;
    }
};

class Solution2 {
public:
    /**
     * @brief 解法二：BK算法演进 (利用 n & (n - 1) 定点清除低位 1)
     *
     * 算法核心：表达式 right & (right - 1) 能够精准消灭 right 二进制中
     * 最右侧的那个 1。因为 right > left，意味着 right 的低位必然存在那些
     * 在递增过程中发生过翻转、不再属于公共前缀的“杂质 1”。
     * 通过不断消灭最右侧的 1，right 会大跨步地向下跳跃，直到其小于或等于 left。
     *
     * 清除杂质 1 的大跨步瞬移图示 (例如 left = 8, right = 15)：
     *
     *   初始: left = 8 (1000), right = 15 (1111)
     *
     *   Loop 1: right = 15 & 14 ➔ 变成 14 (1110) [消灭最右侧的1]
     *   Loop 2: right = 14 & 13 ➔ 变成 12 (1100) [跳过13，消灭下一个1]
     *   Loop 3: right = 12 & 11 ➔ 变成 8  (1000) [跳过11,10,9，直接降到8]
     *
     *   此时 8 > 8 为假，退出循环，剩余的 8 (1000) 即为纯净的公共前缀。
     *
     * @param left 区间左边界 (闭区间)
     * @param right 区间右边界 (闭区间)
     * @return int 区间内所有数字按位与的结果
     *
     * @complexity
     * - 时间复杂度: O(1) - 循环次数仅取决于 right 的二进制中 1 的个数，最多 32
     * 次。
     * - 空间复杂度: O(1) - 零额外空间消耗。
     */
    int rangeBitwiseAnd(int left, int right) {
        while (left < right) {
            right &= right - 1;
        }

        return right;
    }
};
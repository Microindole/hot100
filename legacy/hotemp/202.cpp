#include <unordered_set>

using namespace std;

class Solution1 {
public:
    bool isHappy(int n) {
        unordered_set<int> show;
        show.insert(n);

        while (n != 1) {
            int temp = 0;

            while (n > 0) {
                int w = n % 10;

                temp += w * w;

                n /= 10;
            }

            n = temp;
            if (show.count(n)) {
                return false;
            }

            show.insert(n);
        }

        return true;
    }
};

class Solution2 {
private:
    /**
     * @brief 辅助函数：计算数字 n 各个位上的数字平方和（相当于链表的 next
     * 指针）。
     *
     * @param n 输入的整数
     * @return int 平方和结果
     */
    int getNext(int n) {
        int totalSum = 0;
        while (n > 0) {
            int d = n % 10;
            totalSum += d * d;
            n /= 10;
        }
        return totalSum;
    }

public:
    /**
     * @brief 判断一个正整数是否为“快乐数”（快慢指针法）。
     *
     * @details
     * ### 快慢指针追赶图解 (以 n = 2 为例)
     * @code
     * 阶段 1: 龟兔同跑，寻找相遇点
     * [慢指针] 2 ──► 4 ──► 16 ──► 37 ──► 58 (相遇！退出循环)
     *           ▲                         │
     * [快指针] 2 ─► 16 ─► 58 ─► 145 ─► 20 ─┘ (快指针速度是慢指针的 2 倍)
     *
     * 阶段 2: 判定相遇点是否为 1
     * 相遇在 58 (≠ 1)，说明陷入死循环，返回 false。
     * @endcode
     *
     * ### 复杂度分析
     * - **时间复杂度**: O(log n)。虽然比哈希表法多了一些重复计算，但整体
     *   时间复杂度依然在对数级别。
     * - **空间复杂度**: O(1)。只使用了两个指针变量，做到了常数级空间。
     *
     * @param n 输入的正整数。
     * @return true 如果是快乐数。
     * @return false 如果不是快乐数。
     */
    bool isHappy(int n) {
        int slow = n;
        int fast = getNext(n);

        // 如果没有环（即最终收敛到 1），或者还没相遇，就继续追赶
        while (fast != 1 && slow != fast) {
            slow = getNext(slow);           // 慢指针走一步
            fast = getNext(getNext(fast));  // 快指针走两步
        }

        // 如果是因为等于 1 爬出来的，那就是快乐数；如果是相遇了但不是 1，则有环
        return fast == 1;
    }
};
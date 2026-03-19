#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 对表示整数的数组进行加一操作。
     *
     * 逻辑：
     * 1. 从末尾向前遍历。
     * 2. 遇到小于 9 的数，加 1 后直接返回。
     * 3. 遇到 9，将其置 0，继续循环。
     * 4. 若所有位均为 9，则需在数组首位插入 1。
     *
     * @param digits 输入数组
     * @return vector<int> 加一后的结果
     */
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();

        for (int i = n - 1; i >= 0; i--) {
            if (digits[i] < 9) {
                // 情况 A：没有进位风险，直接加 1 走人
                digits[i]++;
                return digits;
            }
            // 情况 B：当前位是 9，加 1 变 10，本位变 0，继续向高位进位
            digits[i] = 0;
        }

        // 情况 C：全都是 9（如 99 -> 00），需要在前面补 1
        // 技巧：此时数组全为 0，只需在头部插入 1
        digits.insert(digits.begin(), 1);
        return digits;
    }
};
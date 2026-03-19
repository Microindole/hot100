#include <string>

using namespace std;

class Solution {
public:
    /**
     * @brief 判断字符串 s 和 t 是否互为字母异位词（字符种类和数量完全相同）。
     *
     * 算法核心：定长频次哈希阵列 + 严格对等核销。
     * 沿用 383 题的 alpha[26] 静态数组。
     * 先用字符串 s 增加库存，再用字符串 t 扣减库存。
     * 最终检查是否所有字母的计数都刚好回归为 0。
     *
     * @param s 源字符串
     * @param t 目标字符串
     * @return boolean 是否为字母异位词
     *
     * @complexity
     * - 时间复杂度: O(N) - N 为字符串长度。
     * - 空间复杂度: O(1) - 仅消耗固定 26 个整型空间。
     */
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        int alpha[26] = {0};

        for (char ch : s) {
            alpha[ch - 'a']++;
        }

        for (char ch : t) {
            int index = ch - 'a';
            alpha[index]--;

            if (alpha[index] < 0) {
                return false;
            }
        }

        return true;
    }
};
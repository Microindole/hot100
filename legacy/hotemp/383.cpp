#include <string>

using namespace std;

class Solution {
public:
    /**
     * @brief 判断赎金信 ransomNote 能否由杂志 magazine 中的字母构成。
     *
     * 算法核心：定长频次哈希阵列。
     * 鉴于字符集严格限定为 26 个小写英文字母，无需引入复杂的 unordered_map。
     * 直接利用静态数组 alpha[26] 统计 magazine 中各个字符的可用存量。
     * 随后遍历 ransomNote，每消耗一个字符则将计数扣减，若库存不足则判定失败。
     *
     * 字母索引映射与扣减图示 (以 'b' 为例，索引 = 'b' - 'a' = 1)：
     *
     *   Step 1 (统计magazine):  alpha[1]++  ➔  [a:0, b:2, c:0, ...] (库存2个b)
     *   Step 2 (扣减ransomNote): alpha[1]--  ➔  [a:0, b:1, c:0, ...] (消耗1个b)
     *   Step 3 (再次遇到b时):   若发现 alpha[1] == 0 ➔ 无券可用，立刻返回 false
     *
     * @param ransomNote 赎金信字符串
     * @param magazine 杂志字符串
     * @return boolean 能否成功构建
     *
     * @complexity
     * - 时间复杂度: O(M + N) - M 和 N
     * 分别为两字符串的长度，只需各自做单次线性遍历。
     * - 空间复杂度: O(1)   - 仅消耗固定 26
     * 个整型的栈内存空间，与输入规模完全无关。
     */
    bool canConstruct(string ransomNote, string magazine) {
        if (ransomNote.length() > magazine.length()) {
            return false;
        }

        int alpha[26] = {0};

        for (char ch : magazine) {
            alpha[ch - 'a']++;
        }

        for (char ch : ransomNote) {
            int index = ch - 'a';

            if (alpha[index] == 0) {
                return false;
            }

            alpha[index]--;
        }

        return true;
    }
};
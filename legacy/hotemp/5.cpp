#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * longestPalindrome - 中心扩展法
     * @s: 输入字符串
     * * 复杂度：时间 O(n^2)，空间 O(1)
     */
    string longestPalindrome(string s) {
        if (s.length() < 2)
            return s;
        int start = 0, maxLen = 0;

        for (int i = 0; i < s.length(); i++) {
            // 情况 1：回文中心是一个字符 (如 "aba")
            expand(s, i, i, start, maxLen);
            // 情况 2：回文中心是两个字符之间 (如 "abba")
            expand(s, i, i + 1, start, maxLen);
        }
        return s.substr(start, maxLen);
    }

    /**
     * longestPalindrome - 使用 Manacher 算法在线性时间内查找最长回文子串
     * @s: 输入原始字符串
     *
     * 算法原理：
     * 1. 预处理 (Transform):
     * 在字符间插入 '#' 并在首尾添加特殊哨兵 (如 '^' 和 '$')。
     * 目的：将所有回文（奇数/偶数长度）统一视为奇数长度，简化边界处理。
     * 例子: "aba" -> "^#a#b#a#$", "aa" -> "^#a#a#$"
     *
     *
     *
     * 2. 对称性复用 (Mirroring):
     * 维护当前已扩展最远的回文串中心 C 和右边界 R。
     * 对于当前位置 i，其关于 C 的对称点为 j = 2*C - i。
     * - 如果 i < R, 则 d[i] 至少可以继承 min(R - i, d[j])。
     * - 这是因为在 [L, R] 范围内，i 周边的字符分布与 j 周边完全一致。
     *
     *
     *
     * 3. 复杂度分析:
     * - 时间：O(n)。虽然有内层 while 循环，但 R 指针始终单调递增，
     * 且总的成功匹配次数不会超过处理后字符串的长度。
     * - 空间：O(n)。需要额外的数组存储回文半径。
     *
     * 返回值：
     * 提取并返回原始字符串中最长的回文子串。
     *
     *
     *
     * string longestPalindrome(string s) {
     *     if (s.empty())
     *         return "";
     *
     *     // 1. 预处理：插入特殊字符以统一奇偶长度情况
     *     string t = "^";
     *     for (char c : s) {
     *         t += "#";
     *         t += c;
     *     }
     *     t += "#$";
     *
     *     int n = t.length();
     *     // d[i] 存储以 t[i] 为中心的最长回文半径 (包含 t[i] 本身)
     *     vector<int> d(n, 0);
     *     int C = 0;
     *     int R = 0;
     *
     *     int maxLen = 0;
     *     int centerIndex = 0;
     *
     *     for (int i = 1; i < n - 1; i++) {
     *         // 如果 i 在当前右边界内，利用对称性初始化半径
     *         if (i < R) {
     *             int j = 2 * C - i;
     *             d[i] = min(R - i, d[j]);
     *         }
     *
     *         // 尝试以 i 为中心继续向外暴力扩展
     *         while (t[i + (d[i] + 1)] == t[i - (d[i] + 1)]) {
     *             d[i]++;
     *         }
     *
     *         // 如果当前回文串超过了原有的右边界，更新中心和边界
     *         if (i + d[i] > R) {
     *             C = i;
     *             R = i + d[i];
     *         }
     *
     *         // 记录全局最长回文半径及其对应的中心
     *         if (d[i] > maxLen) {
     *             maxLen = d[i];
     *             centerIndex = i;
     *         }
     *     }
     *
     *     // 结果映射逻辑：
     *     // 经过 # 填充后，d[i] 的值恰好等于原字符串中回文串的长度。
     *     // 起始索引计算：(中心点索引 - 最大半径) / 2
     *     //
     *     int start = (centerIndex - maxLen) / 2;
     *     return s.substr(start, maxLen);
     * }
     */

private:
    void expand(string& s, int l, int r, int& start, int& maxLen) {
        while (l >= 0 && r < s.length() && s[l] == s[r]) {
            l--;
            r++;
        }
        // 循环停止时，s[l+1 ... r-1] 是回文，
        // 长度为 (r-1) - (l+1) + 1 = r - l -1
        if (r - l - 1 > maxLen) {
            start = l + 1;
            maxLen = r - l - 1;
        }
    }
};
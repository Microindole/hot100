#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    /**
     * @brief 给定两个二进制字符串，返回它们的二进制求和结果。
     *
     * 算法模拟竖式加法，使用双指针从字符串末尾（低位）向开头（高位）遍历。
     * 核心逻辑与“两数相加”一致，采用逢二进一（Base-2）的规则。
     *
     * 二进制竖式加法图示 (例如: "11" + "1" = "100")：
     *
     *   字符串 a:      1   1  (索引 i 指向末尾)
     *   字符串 b:          1  (索引 j 指向末尾)
     *                -------
     *   按位相加:      1   2
     *   进位 carry:   1   1  (初始为 0)
     *                -------
     *   临时结果:     "001"   (动态追加得到，需反转)
     *   最终逆序:     "100"
     *
     * @param a 二进制字符串1
     * @param b 二进制字符串2
     * @return string 求和后的二进制字符串
     *
     * @complexity
     * - 时间复杂度: O(max(N, M)) - N 和 M 分别为两字符串长度，单次线性扫描。
     * - 空间复杂度: O(1) - 除去存储返回结果的字符串外，仅消耗常数级辅助空间。
     */
    string addBinary(string a, string b) {
        string res = "";
        int i = a.size() - 1;
        int j = b.size() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;

            if (i >= 0) {
                sum += a[i] - '0';
                i--;
            }
            if (j >= 0) {
                sum += b[j] - '0';
                j--;
            }

            carry = sum / 2;
            res.push_back((sum % 2) + '0');
        }

        reverse(res.begin(), res.end());
        return res;
    }
};
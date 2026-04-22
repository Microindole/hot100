#include <algorithm>
#include <string>
#include <vector>

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        // 1. 预处理
        std::string T = "$#";
        for (char c : s) {
            T += c;
            T += "#";
        }
        T += "@";  // 首尾添加不同字符防止越界

        int n = T.length();
        std::vector<int> p(n, 0);
        int center = 0, maxRight = 0;
        int maxLen = 0, resCenter = 0;

        for (int i = 1; i < n - 1; ++i) {
            // 2. 核心跳跃：i 在 maxRight 内部时利用对称性
            if (i < maxRight) {
                p[i] = std::min(maxRight - i, p[2 * center - i]);
            } else {
                p[i] = 1;
            }

            // 3. 中心扩展（暴力尝试延伸）
            while (T[i + p[i]] == T[i - p[i]]) {
                p[i]++;
            }

            // 4. 更新 center 和 maxRight
            if (i + p[i] > maxRight) {
                center = i;
                maxRight = i + p[i];
            }

            // 记录最大值
            if (p[i] > maxLen) {
                maxLen = p[i];
                resCenter = i;
            }
        }

        // 5. 还原回原字符串
        int start = (resCenter - maxLen) / 2;
        return s.substr(start, maxLen - 1);
    }
};
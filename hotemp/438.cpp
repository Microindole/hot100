#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int s_len = s.length(), p_len = p.length();
        if (s_len < p_len) return {};

        vector<int> res;
        vector<int> s_cnt(26, 0);
        vector<int> p_cnt(26, 0);

        // 1. 初始化统计 p 的字符和 s 的第一个窗口
        for (int i = 0; i < p_len; i++) {
            p_cnt[p[i] - 'a']++;
            s_cnt[s[i] - 'a']++;
        }

        // 2. 检查第一个窗口是否匹配
        if (s_cnt == p_cnt) {
            res.push_back(0);
        }

        // 3. 开始滑动窗口
        // i 是窗口左侧即将离开的字符下标
        for (int i = 0; i < s_len - p_len; i++) {
            // 窗口右移：左出右进
            s_cnt[s[i] - 'a']--;          // 左侧字符离开
            s_cnt[s[i + p_len] - 'a']++;  // 右侧新字符进入

            // vector 在 C++ 中重载了 == 运算符，比较复杂度为 O(26)
            if (s_cnt == p_cnt) {
                res.push_back(i + 1);
            }
        }

        return res;
    }
};
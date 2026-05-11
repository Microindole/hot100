#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        // 使用映射表存储数值，查表比一堆 if-else 更清晰
        unordered_map<char, int> rti = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};

        int res = 0;
        int n = s.size();

        for (int i = 0; i < n; i++) {
            // 如果当前位比后一位小，则减去当前位（如 IV: -1 + 5）
            if (i < n - 1 && rti[s[i]] < rti[s[i + 1]]) {
                res -= rti[s[i]];
            } else {
                res += rti[s[i]];
            }
        }
        return res;
    }
};
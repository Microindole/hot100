#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        // 按照面值从大到小排列
        // 包含 7 个基础符号和 6 个特殊的减法组合
        int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        string symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        string res = "";

        for (int i = 0; i < 13; i++) {
            // 贪心：只要还能减掉当前面值，就一直减
            while (num >= values[i]) {
                num -= values[i];
                res += symbols[i];
            }
            // 如果数字已经减为 0，可以直接提前跳出
            if (num == 0) break;
        }

        return res;
    }
};
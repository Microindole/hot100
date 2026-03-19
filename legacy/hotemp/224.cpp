#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    /**
     * @brief 实现一个基本的计算器来计算简单的字符串表达式的值。
     *
     * 表达式字符串包含括号 '('、')'、加号 '+'、减号 '-'、
     * 非负整数和空格 ' '。本解法利用一个栈来维护当前的符号状态，
     * 遇到括号时将当前的全局符号压栈，从而实现括号的动态展开。
     *
     * @b 符号栈状态演变 (以 1 - (5 - 3) 为例):
     * @code
     *   字符 :  1    -    (    5    -    3    )
     *   sign :  1   -1   -1   -1    1    1   -1
     *   ops  : [1]  [1] [1,-1] [-1] [-1] [-1] [1]
     *   res  :  1    1    1   -4   -4   -1   -1
     * @endcode
     *
     * @param s 待计算的有效中缀表达式字符串。
     * @return int 表达式的计算结果。
     */
    int calculate(string s) {
        stack<int> ops;
        ops.push(1);

        int sign = 1;
        int res = 0;
        int n = s.length();
        int i = 0;

        while (i < n) {
            if (s[i] == ' ') {
                i++;
            } else if (s[i] == '+') {
                sign = ops.top();
                i++;
            } else if (s[i] == '-') {
                sign = -ops.top();
                i++;
            } else if (s[i] == '(') {
                ops.push(sign);
                i++;
            } else if (s[i] == ')') {
                ops.pop();
                i++;
            } else {
                long num = 0;
                while (i < n && s[i] >= '0' && s[i] <= '9') {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }

                res += sign * num;
            }
        }
        return res;
    }
};

int main() {
    string exp = "1 - ( 5 - 3 )";
    Solution sol;

    cout << exp << " = " << sol.calculate(exp) << endl;
    return 0;
}
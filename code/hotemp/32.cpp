#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int res = 0;
        int left = 0, right = 0;

        for (char c : s) {
            if (c == '(')
                left++;
            else
                right++;

            if (left == right) {
                res = max(res, 2 * left);
            } else if (right > left) {
                left = 0;
                right = 0;
            }
        }

        left = 0;
        right = 0;

        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '(')
                left++;
            else
                right++;
            if (left == right)
                res = max(res, right * 2);
            else if (left > right) {
                left = 0;
                right = 0;
            }
        }

        return res;
    }
};

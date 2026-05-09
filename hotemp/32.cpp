#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int res = 0;

        int left = 0, right = 0;
        int n = s.size();

        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                left++;
            } else {
                right++;
            }

            if (left == right) {
                res = max(res, 2 * left);
            } else if (right > left) {
                right = 0;
                left = 0;
            }
        }

        left = 0;
        right = 0;

        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == ')') {
                right++;
            } else {
                left++;
            }

            if (left == right) {
                res = max(res, 2 * right);

            } else if (left > right) {
                left = 0;
                right = 0;
            }
        }

        return res;
    }
};

int main() {
    string s;
    cin >> s;
    Solution so;

    while (s != "#") {
        cout << so.longestValidParentheses(s) << endl;
        cin >> s;
    }

    return 0;
}
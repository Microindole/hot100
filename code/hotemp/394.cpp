#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        stack<int> nums;
        stack<string> strs;

        string cur = "";
        int num = 0;

        for (char c : s) {
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            } else if (c == '[') {
                nums.push(num);
                strs.push(cur);

                num = 0;
                cur = "";
            } else if (c == ']') {
                int times = nums.top();
                nums.pop();

                string prev = strs.top();
                strs.pop();

                string repeated = "";
                while (times--) {
                    repeated += cur;
                }

                cur = prev + repeated;
            } else {
                cur.push_back(c);
            }
        }

        return cur;
    }
};

int main() {
    string s = "abc3[cd]xyz";

    Solution sol;

    cout << sol.decodeString(s) << endl;
}
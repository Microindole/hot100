#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> valid;

        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                valid.push(c);
            }

            else {
                if (valid.empty())
                    return false;
                if (c == ')') {
                    if (valid.top() != '(')
                        return false;

                    valid.pop();
                } else if (c == ']') {
                    if (valid.top() != '[')
                        return false;

                    valid.pop();
                } else if (c == '}') {
                    if (valid.top() != '{')
                        return false;

                    valid.pop();
                }
            }
        }

        return valid.empty();
    }
};
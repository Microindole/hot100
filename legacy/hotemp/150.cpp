#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;

        for (const string& str : tokens) {
            if (str == "+" || str == "-" || str == "*" || str == "/") {
                int op2 = st.top();
                st.pop();

                int op1 = st.top();
                st.pop();

                if (str == "+") {
                    st.push(op1 + op2);
                } else if (str == "-") {
                    st.push(op1 - op2);
                } else if (str == "*") {
                    st.push(op1 * op2);
                } else {
                    st.push(op1 / op2);
                }
            }

            else {
                st.push(stoi(str));
            }
        }

        return st.top();
    }
};
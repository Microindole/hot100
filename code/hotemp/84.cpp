#include <climits>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> h;
        h.push_back(0);
        for (int i : heights) {
            h.push_back(i);
        }
        h.push_back(0);

        stack<int> st;

        int res = 0;
        for (int i = 0; i < h.size(); i++) {
            while (!st.empty() && h[st.top()] > h[i]) {
                int top = st.top();
                st.pop();

                res = max(h[top] * (i - st.top() - 1), res);
            }

            st.push(i);
        }

        return res;
    }
};
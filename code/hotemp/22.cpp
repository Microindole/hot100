#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    void dfs(vector<string>& res, string& str, int left, int right, int n) {
        if (left == n && right == n) {
            res.push_back(str);
            return;
        }

        // 还能放左括号
        if (left < n) {
            str.push_back('(');

            dfs(res, str, left + 1, right, n);

            str.pop_back();
        }

        // 右括号数量必须小于左括号数量
        if (right < left) {
            str.push_back(')');

            dfs(res, str, left, right + 1, n);

            str.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        string str = "";
        vector<string> res;

        dfs(res, str, 0, 0, n);

        return res;
    }
};
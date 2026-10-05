#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isValid(vector<string>& ans, int row, int col, int n) {
        for (int i = 0; i < row; i++) {
            if (ans[i][col] == 'Q')
                return false;
        }

        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (ans[i][j] == 'Q')
                return false;
        }

        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (ans[i][j] == 'Q')
                return false;
        }

        return true;
    }

    void dfs(vector<vector<string>>& res, vector<string>& ans, int index,
             int n) {
        if (index == n) {
            res.push_back(ans);
            return;
        }

        for (int i = 0; i < n; i++) {
            if (isValid(ans, index, i, n)) {
                ans[index][i] = 'Q';
                dfs(res, ans, index + 1, n);
                ans[index][i] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> ans(n, string(n, '.'));

        dfs(res, ans, 0, n);

        return res;
    }
};
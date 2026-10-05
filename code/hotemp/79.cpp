#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    void dfs(vector<vector<char>>& board, string& word,
             vector<vector<bool>>& canUse, int i, int j, bool& res, int index) {
        if (index == word.size()) {
            res = true;
            return;
        }

        int m = board.size(), n = board[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || canUse[i][j] == false ||
            board[i][j] != word[index]) {
            return;
        }

        canUse[i][j] = false;

        dfs(board, word, canUse, i - 1, j, res, index + 1);
        dfs(board, word, canUse, i + 1, j, res, index + 1);
        dfs(board, word, canUse, i, j + 1, res, index + 1);
        dfs(board, word, canUse, i, j - 1, res, index + 1);

        canUse[i][j] = true;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();

        int size = word.size();

        vector<vector<bool>> canUse(m, vector<bool>(n, true));

        bool res = false;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) {
                    dfs(board, word, canUse, i, j, res, 0);
                }
            }
        }

        return res;
    }
};

int main() {
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};

    string word = "ABCCED";

    Solution sol;

    cout << sol.exist(board, word) << endl;
}
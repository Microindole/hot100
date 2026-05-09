#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int rows = board.size();
        if (rows == 0) return;
        int cols = board[0].size();

        // 1. 遍历左右边界
        for (int i = 0; i < rows; ++i) {
            dfs(board, i, 0);         // 左边界
            dfs(board, i, cols - 1);  // 右边界
        }

        // 2. 遍历上下边界
        for (int j = 0; j < cols; ++j) {
            dfs(board, 0, j);         // 上边界
            dfs(board, rows - 1, j);  // 下边界
        }

        // 3. 最终遍历：把 'O' 变成 'X'，把 'Y' 还原回 'O'
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                } else if (board[i][j] == 'Y') {
                    board[i][j] = 'O';
                }
            }
        }
    }

private:
    void dfs(vector<vector<char>>& board, int r, int c) {
        int rows = board.size();
        int cols = board[0].size();

        // 递归终止条件：越界、或者当前不是 'O'（包括已经是 'X' 或 'Y' 的情况）
        if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != 'O') {
            return;
        }

        // 标记为 'Y'
        board[r][c] = 'Y';

        // 向四个方向扩散
        dfs(board, r + 1, c);
        dfs(board, r - 1, c);
        dfs(board, r, c + 1);
        dfs(board, r, c - 1);
    }
};
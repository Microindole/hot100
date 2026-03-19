#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 利用二进制复合位实现原地的 $3 \times 3$ 卷积细胞自动机。
     *
     * 算法核心：每一个细胞包含两个维度的状态：
     * - 第 0 位 (最低位)：当前(旧)状态
     * - 第 1 位 (次低位)：下一轮(新)状态
     *
     * 邻域 8 方向卷积核 (Kernel) 示意图：
     *   [ 1 ] [ 1 ] [ 1 ]      卷积计算时，通过 (board[r][c] & 1)
     *   [ 1 ] [ 0 ] [ 1 ]  ➔  过滤掉第 1 位的干扰，精准提取邻居的旧状态，
     *   [ 1 ] [ 1 ] [ 1 ]      从而完美实现“原地无污染修改”。
     *
     * @param board m x n 的细胞状态矩阵 (0为死，1为活)
     */
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();

        int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                          {0, 1},   {1, -1}, {1, 0},  {1, 1}};

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int live_neighbors = 0;

                for (auto& d : dirs) {
                    int r = i + d[0];
                    int c = j + d[1];
                    if (r >= 0 && r < m && c >= 0 && c < n) {
                        live_neighbors += (board[r][c] & 1);
                    }
                }

                if (board[i][j] == 1) {
                    if (live_neighbors == 2 || live_neighbors == 3) {
                        board[i][j] |= 2;
                    }
                } else {
                    if (live_neighbors == 3) {
                        board[i][j] |= 2;
                    }
                }
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] >>= 1;
            }
        }
    }
};
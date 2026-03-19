#include <vector>

using namespace std;

class Solution {
public:
    void setAns(int& up, int& down, int& left, int& right, vector<int>& res,
                vector<vector<int>>& matrix) {
        if (up == down) {
            for (int i = left; i <= right; i++) {
                res.push_back(matrix[up][i]);
            }
        } else if (left == right) {
            for (int i = up; i <= down; i++) {
                res.push_back(matrix[i][left]);
            }
        } else {
            for (int i = left; i <= right; i++) {
                res.push_back(matrix[up][i]);
            }
            for (int i = up + 1; i <= down; i++) {
                res.push_back(matrix[i][right]);
            }
            for (int i = right - 1; i >= left; i--) {
                res.push_back(matrix[down][i]);
            }
            for (int i = down - 1; i >= up + 1; i--) {
                res.push_back(matrix[i][left]);
            }
        }

        left++;
        right--;
        up++;
        down--;
    }

    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int left = 0, right = matrix[0].size() - 1;
        int up = 0, down = matrix.size() - 1;

        vector<int> res;

        while (left <= right && up <= down) {
            setAns(up, down, left, right, res, matrix);
        }

        return res;
    }
};

class Solution2 {
public:
    /**
     * @brief 按照顺时针螺旋顺序，返回矩阵中的所有元素。
     *
     * 算法核心：四指针边界收缩法。
     * 维护 up, down, left, right 四个边界，每次顺时针顺次遍历外层的四条边。
     * 每遍历完一条边，对应的边界线就向内收缩一格，直至边界交叠错位。
     *
     * 螺旋遍历与边界收缩图示：
     *
     *      left                   right
     *   up  ➔  ➔  ➔  ➔  ➔  ➔  ➔  ➔  ↴  (遍历完上边，up++)
     *       ▲  [ 1 ]  [ 2 ]  [ 3 ]  │
     *       │  [ 8 ]  [ 9 ]  [ 4 ]  ▼  (遍历完右边，right--)
     *       │  [ 7 ]  [ 6 ]  [ 5 ]  │
     *  down ◀  ⬅  ⬅  ⬅  ⬅  ⬅  ⬅  ⬅  ↵  (遍历完下边，down--)
     *                                  (遍历完左边，left++)
     *
     * @param matrix m x n 的二维整数矩阵
     * @return vector<int> 顺时针螺旋排列的一维数组
     *
     * @complexity
     * - 时间复杂度: O(M * N) - M 和 N
     * 分别为矩阵的行数和列数，每个元素仅访问一次。
     * - 空间复杂度: O(1) - 除去存储结果的 res 容器外，仅消耗常数级边界变量。
     */
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if (matrix.empty() || matrix[0].empty())
            return res;

        // 初始化上下左右四个边界
        int up = 0, down = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;

        while (left <= right && up <= down) {
            // 1. 从左到右遍历上边
            for (int i = left; i <= right; i++) {
                res.push_back(matrix[up][i]);
            }
            up++;  // 上边界下移

            // 2. 从上到下遍历右边
            for (int i = up; i <= down; i++) {
                res.push_back(matrix[i][right]);
            }
            right--;  // 右边界左移

            // 3. 安全防御：防止在单行/单列情况下重复遍历
            if (up <= down) {
                // 从右到左遍历下边
                for (int i = right; i >= left; i--) {
                    res.push_back(matrix[down][i]);
                }
                down--;  // 下边界上移
            }

            // 4. 安全防御：防止在单行/单列情况下重复遍历
            if (left <= right) {
                // 从下到上遍历左边
                for (int i = down; i >= up; i--) {
                    res.push_back(matrix[i][left]);
                }
                left++;  // 左边界右移
            }
        }

        return res;
    }
};
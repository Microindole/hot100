#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 给定一个 n x n 的二维矩阵，将其顺时针旋转 90 度。
     *
     * 算法采用线性代数变换法（转置 + 左右翻转），避免了复杂的四角联动交换：
     *
     * 变换步骤几何图示：
     *
     *   原始矩阵:       Step 1: 主对角线翻转     Step 2: 左右翻转 (最终结果)
     *   [1, 2, 3]        [1, 4, 7]             [7, 4, 1]
     *   [4, 5, 6]  ➔    [2, 5, 8]      ➔     [8, 5, 2]
     *   [7, 8, 9]        [3, 6, 9]             [9, 6, 3]
     *
     * @param matrix 严格为 n x n 的正方形二维整数矩阵 (原地修改)
     *
     * @complexity
     * - 时间复杂度: O(N^2)
     *     N 为矩阵的边长。
     *     转置访问约一半元素，翻转访问全部元素，
     *     总共耗时依然与元素总数成正比。
     * - 空间复杂度: O(1)
     *     直接在原矩阵上通过 std::swap 进行原地修改，无额外空间。
     */
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // 1. 主对角线翻转 (注意 j 从 i + 1 开始，
        // 只遍历右上三角，防止重复交换换回来)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // 2. 左右翻转 (遍历每一行，直接调用标准库的 reverse 函数)
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};
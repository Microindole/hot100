#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 判断一个 9x9 的数独棋盘是否有效。
     *
     * 算法核心：单次遍历 + 哈希状态阵列。
     * 引入三个布尔矩阵分别记录每行、每列以及每个 3x3 九宫格内数字 1-9
     * 的占用情况。 遍历到棋盘坐标 (i, j)
     * 时，若发现数字已在对应的行、列或九宫格中存在，则立刻判定无效。
     *
     * 九宫格索引映射图示 (k = (i / 3) * 3 + (j / 3))：
     *
     *      j = 0 1 2   3 4 5   6 7 8
     *    i = 0 [ 0 ]   [ 1 ]   [ 2 ]
     *        1 [box]   [box]   [box]
     *        2
     *
     *        3 [ 3 ]   [ 4 ]   [ 5 ]
     *        4 [box]   [box]   [box]
     *        5
     *
     *        6 [ 6 ]   [ 7 ]   [ 8 ]
     *        7 [box]   [box]   [box]
     *        8
     *
     * @param board 9x9 的数独字符棋盘，'.' 表示空位
     * @return boolean 棋盘是否合法
     *
     * @complexity
     * - 时间复杂度: O(1) - 棋盘大小固定为 9x9 = 81 个单元格，遍历次数恒定。
     * - 空间复杂度: O(1) - 哈希数组大小固定为 3 * 9 * 10 字节，消耗常数级空间。
     */
    bool isValidSudoku(vector<vector<char>>& board) {
        // 使用二维静态数组模拟哈希表，效率远高于 std::unordered_set
        // rows[i][num] 记录第 i 行里数字 num 是否出现过
        bool rows[9][10] = {false};
        bool cols[9][10] = {false};
        bool boxes[9][10] = {false};

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                // 如果是空位，直接跳过
                if (board[i][j] == '.') {
                    continue;
                }

                // 将字符数字转换为整型索引 (1-9)
                int num = board[i][j] - '0';

                // 计算当前坐标属于第几个九宫格 (0-8)
                int box_index = (i / 3) * 3 + (j / 3);

                // 贪心防御：只要在任意一个维度上露过面，立刻返回不合法
                if (rows[i][num] || cols[j][num] || boxes[box_index][num]) {
                    return false;
                }

                // 鸣枪注册：将当前数字在三个维度里全部标记为“已存在”
                rows[i][num] = true;
                cols[j][num] = true;
                boxes[box_index][num] = true;
            }
        }

        return true;
    }
};
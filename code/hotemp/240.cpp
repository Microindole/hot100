#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = 0, col = matrix[0].size() - 1;

        int rows = matrix.size();

        while (row < rows && col >= 0) {
            int temp = matrix[row][col];

            if (temp == target) {
                return true;
            } else if (temp < target) {
                row++;
            } else {
                col--;
            }
        }

        return false;
    }
};

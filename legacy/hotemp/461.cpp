class Solution {
public:
    int hammingDistance(int x, int y) {
        int z = x ^ y;
        int count = 0;
        while (z > 0) {
            z &= (z - 1);  // 清除最右边的 1
            count++;
        }
        return count;
    }
};
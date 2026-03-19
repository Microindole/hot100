#include <iostream>

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) {
            return n;
        }

        int b1 = 1, b2 = 2;
        int res = 0;

        int index = 3;
        while (index <= n) {
            res = b1 + b2;
            b1 = b2;
            b2 = res;

            index++;
        }

        return res;
    }
};
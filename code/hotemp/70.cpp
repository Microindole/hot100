#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 3) {
            return n;
        } else {
            int a1 = 1, a2 = 2;
            int a3;

            for (int i = 0; i < n - 2; i++) {
                a3 = a1 + a2;
                a1 = a2;
                a2 = a3;
            }

            return a3;
        }
    }
};
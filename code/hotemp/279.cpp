#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int numSquares(int n) {
    vector<int> arr;

    for (int i = 1; i * i <= n; i++) {
        arr.push_back(i * i);
    }

    // n 本身就是完全平方数，直接返回
    if (arr.back() == n) {
        return 1;
    }

    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int square : arr) {
            if (square > i) {
                break;
            }

            dp[i] = min(dp[i], dp[i - square] + 1);
        }
    }

    return dp[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
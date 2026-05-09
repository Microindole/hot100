#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int numSquares(int n) {
    int size = 1;
    while (size * size <= n) {
        size++;
    }
    size--;

    vector<int> arr(size, 0);
    if (n == arr[size - 1] * arr[size - 1]) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = (i + 1) * (i + 1);
    }

    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j : arr) {
            if (i - j >= 0) {
                dp[i] = min(dp[i], dp[i - j] + 1);
            }
        }
    }

    return dp[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
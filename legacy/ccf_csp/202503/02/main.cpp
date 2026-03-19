#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> A(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        cin >> A[i];
    }

    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i && j <= m; j++) {
            dp[i] = max(dp[i], dp[i - j] + A[j]);
        }
    }
    cout << dp[n] << endl;
}

/*
10 5
1 3 5 3 1

4 3
1 60 100
*/
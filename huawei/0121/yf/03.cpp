#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, T, m;
    cin >> n >> T >> m;

    vector<vector<int>> dp(T + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < n; i++) {
        int t, p;
        cin >> t >> p;

        int heavy = (t > 30) ? 1 : 0;

        for (int j = T; j >= t; j--) {
            for (int k = m; k >= heavy; k--) {
                dp[j][k] = max(dp[j][k], dp[j - t][k - heavy] + p);
            }
        }
    }

    cout << dp[T][m];

    return 0;
}
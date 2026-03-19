#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int T;
    cin >> T;

    vector<int> res;

    while (T--) {
        string s;
        cin >> s;

        int n = s.size();

        vector<vector<int>> dp(n + 1, vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = 1;

        for (int i = 0; i < n; i++) {
            if (s[i] <= 'z' && s[i] >= 'a') {
                dp[i + 1][0] = min(dp[i][0] + 1, dp[i][1] + 2);
                dp[i + 1][1] = min(dp[i][0] + 2, dp[i][1] + 2);
            } else {
                dp[i + 1][0] = min(dp[i][0] + 2, dp[i][1] + 2);
                dp[i + 1][1] = min(dp[i][0] + 2, dp[i][1] + 1);
            }
        }

        res.push_back(max(dp[n][0], dp[n][1]));
    }

    for (int i : res) {
        cout << i << endl;
    }

    return 0;
}
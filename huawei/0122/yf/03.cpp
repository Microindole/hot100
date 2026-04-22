#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct cake {
    int x, y, z;
};

int main() {
    int n, w, e, k;
    cin >> n >> w >> e >> k;

    vector<cake> cakes(n);
    for (int i = 0; i < n; i++) {
        cin >> cakes[i].x;
    }

    for (int i = 0; i < n; i++) {
        cin >> cakes[i].y;
    }

    for (int i = 0; i < n; i++) {
        cin >> cakes[i].z;
    }

    sort(cakes.begin(), cakes.end(), [](const cake& a, const cake& b) { return a.x < b.x; });

    vector<vector<int>> dp(e + 1, vector<int>(k + 1, -1));
    dp[0][0] = w;

    for (int i = 0; i < n; i++) {
        for (int j = e - cakes[i].z; j >= 0; j--) {
            for (int p = k - 1; p >= 0; p--) {
                if (dp[j][p] >= cakes[i].x) {
                    dp[j + cakes[i].z][p + 1] = max(dp[j + cakes[i].z][p + 1], dp[j][p] + cakes[i].y);
                }
            }
        }
    }

    int maxz = -1;
    int maxk = 0;

    for (int i = 0; i <= e; i++) {
        for (int j = 1; j <= k; j++) {
            if (dp[i][j] > maxz) {
                maxz = dp[i][j];
                maxk = j;
            } else if (dp[i][j] == maxz && maxz != -1) {
                if (j < maxk) {
                    maxk = j;
                }
            }
        }
    }

    if (maxz < w) {
        cout << w << " " << 0 << endl;

    } else {
        cout << maxz << " " << maxk << endl;
    }

    return 0;
}
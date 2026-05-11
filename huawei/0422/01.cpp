#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 定义一个足够大的数表示无法到达
const int INF = 1e9;

int solve() {
    int m, n;
    // 维度校验：如果输入无效直接返回 -1
    if (!(cin >> m >> n) || m <= 0 || m > 100 || n <= 0 || n > 100) {
        return -1;
    }

    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    // 起点或终点有障碍物，无法通行
    if (grid[0][0] != 0 || grid[m - 1][n - 1] != 0) {
        return -1;
    }

    // dp[i][j][0] 表示“横着”进入该格子的最少转向次数（从左边来）
    // dp[i][j][1] 表示“竖着”进入该格子的最少转向次数（从上面来）
    vector<vector<vector<int>>> dp(m,
                                   vector<vector<int>>(n, vector<int>(2, INF)));

    // 初始化起点：由于起点没有前一格，不计转向，两个状态都设为 0
    dp[0][0][0] = 0;
    dp[0][0][1] = 0;

    // --- 初筛第一行 ---
    for (int j = 1; j < n; ++j) {
        if (grid[0][j] == 0 && dp[0][j - 1][0] != INF) {
            dp[0][j][0] = 0;  // 沿着第一行一直往右走，转向次数始终为 0
        } else {
            break;  // 遇到障碍物，后面都无法通过第一行到达
        }
    }

    // --- 初筛第一列 ---
    for (int i = 1; i < m; ++i) {
        if (grid[i][0] == 0 && dp[i - 1][0][1] != INF) {
            dp[i][0][1] = 0;  // 沿着第一列一直往下走，转向次数始终为 0
        } else {
            break;  // 遇到障碍物，后面都无法通过第一列到达
        }
    }

    // --- 遍历剩下的格子 ---
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            if (grid[i][j] != 0) continue;  // 障碍物直接跳过（保持 INF）

            // 1. 计算 dp[i][j][0] (向右进入)
            // 可以从左边格子的“向右”状态过来（不转向）
            // 也可以从左边格子的“向下”状态过来（转向 +1）
            dp[i][j][0] = min(dp[i][j - 1][0], dp[i][j - 1][1] + 1);

            // 2. 计算 dp[i][j][1] (向下进入)
            // 可以从上面格子的“向下”状态过来（不转向）
            // 也可以从上面格子的“向右”状态过来（转向 +1）
            dp[i][j][1] = min(dp[i - 1][j][1], dp[i - 1][j][0] + 1);
        }
    }

    // 结果取两种进入方式的最小值
    int ans = min(dp[m - 1][n - 1][0], dp[m - 1][n - 1][1]);
    return (ans >= INF) ? -1 : ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << solve() << endl;
    return 0;
}
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    // 基础优化
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if (!(cin >> n))
        return 0;

    vector<int> a(n + 1);
    vector<int> k(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> k[i];

    // dist[i] 存储到达第 i 个格子的最少跳跃次数
    // 初始化为 -1，表示该格子尚未到达（起到 set 的去重作用）
    vector<int> dist(n + 1, -1);

    queue<int> q;

    // 初始状态：站在第 1 个格子，步数为 0
    q.push(1);
    dist[1] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // 如果已经到了第 n 个格子，直接输出结果
        if (u == n) {
            cout << dist[u] << endl;
            return 0;
        }

        // 尝试从当前格子 u 跳到 [u + 1, min(n, u + ku)] 中的每一个落地格 j
        int max_jump = min((long long)n, (long long)u + k[u]);
        for (int j = u + 1; j <= max_jump; j++) {
            // 落地后强制后退 aj，得到实际停下的位置 target
            int target = j - a[j];

            // 核心判断：如果这个实际位置 target 之前没来过
            if (target >= 1 && target <= n && dist[target] == -1) {
                dist[target] = dist[u] + 1;
                q.push(target);
            }
        }
    }

    // 如果队列空了还没搜到 n，说明无法到达
    cout << -1 << endl;

    return 0;
}
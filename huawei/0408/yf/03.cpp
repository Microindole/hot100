#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
    // 提高输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    ll C, M;
    if (!(cin >> n >> C >> M)) return 0;

    vector<ll> ci(n), mi(n), vi(n);
    for (int i = 0; i < n; i++) {
        cin >> ci[i] >> mi[i] >> vi[i];
    }

    int total_masks = 1 << n;

    // 1. 初始预处理：计算“刚好”能塞进一台服务器的任务集合
    vector<ll> V(total_masks, 0);
    for (int mask = 0; mask < total_masks; mask++) {
        ll sumC = 0, sumM = 0, sumV = 0;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                sumC += ci[i];
                sumM += mi[i];
                sumV += vi[i];
            }
        }
        // 只有不超重，才记录这个组合的总价值
        if (sumC <= C && sumM <= M) {
            V[mask] = sumV;
        }
    }

    // 2. 【核心修正】：子集最大值传递
    // 这一步确保了 V[mask] 代表：在 mask 范围内任选，一台机器能拿到的最大值。
    // 这解决了“全选超重但只选一部分不超重”的问题。
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < total_masks; mask++) {
            if (mask & (1 << i)) {
                V[mask] = max(V[mask], V[mask ^ (1 << i)]);
            }
        }
    }

    // 3. 状压 DP
    // dp[mask] 表示在当前服务器数量下，面对任务池 mask 能获得的最大价值
    vector<ll> dp = V;  // 初始状态即为 1 台服务器的结果

    // 输出 1 台服务器的结果
    cout << dp[total_masks - 1] << "\n";

    // 计算从 2 到 n 台服务器的情况
    for (int k = 2; k <= n; k++) {
        vector<ll> next_dp = dp;
        for (int mask = total_masks - 1; mask > 0; mask--) {
            // 枚举子集优化：O(3^n)
            for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
                // 这里的逻辑是：给第 k 台机器分配 sub 任务，剩下的分给前 k-1 台
                if (V[sub] > 0) {
                    next_dp[mask] = max(next_dp[mask], dp[mask ^ sub] + V[sub]);
                }
            }
        }
        dp = next_dp;
        cout << dp[total_masks - 1] << "\n";
    }

    return 0;
}
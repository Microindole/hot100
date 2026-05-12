#include <iostream>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
const ll INV2 = 500000004;  // 2在模10^9+7下的逆元

ll get_sum(ll n) {
    if (n <= 0)
        return 0;

    // 第一部分：n^2 (n个n相加)
    ll res = (n % MOD) * (n % MOD) % MOD;

    // 第二部分：整除分块计算 sum( i * floor(n/i) )
    ll part2 = 0;
    for (ll l = 1, r; l <= n; l = r + 1) {
        ll k = n / l;  // 当前块的商
        if (k == 0) {  // 如果商为0，说明 l 已经很大了，后面全是0
            r = n;
        } else {
            r = min(n, n / k);  // 算出当前块的右边界
        }

        // 计算区间 [l, r] 的和：(l + r) * (r - l + 1) / 2
        ll count = (r - l + 1) % MOD;
        ll sum_lr = (l + r) % MOD * count % MOD * INV2 % MOD;

        // 该块的贡献：商 * 区间i的总和
        ll cur_contribution = (k % MOD) * sum_lr % MOD;
        part2 = (part2 + cur_contribution) % MOD;
    }

    // 最终：n^2 - part2
    return (res - part2 + MOD) % MOD;
}

int main() {
    // 优化输入输出
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        ll n, m;
        cin >> n >> m;

        // 计算 f(n) 和 f(m)
        ll fn = get_sum(n);
        ll fm = get_sum(m);

        // 结果相乘
        cout << (fn * fm % MOD) << "\n";
    }
    return 0;
}
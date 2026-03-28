/*
 // vec:vector<int>
int index = 2; // 想删除索引为 2 的元素
vec.erase(vec.begin() + index);
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

// 模拟函数：计算从位置 pos 降落所需的最小初始攻击力
ll get_p(int pos, int n, const vector<ll>& a, const vector<ll>& b) {
    int L = pos, R = pos + 1;
    ll current_atk = 0;  // 当前攻击力
    ll start_atk = 0;    // 累计需要的初始攻击力

    while (L >= 1 || R <= n) {
        int target;
        // 贪心：选择两边防御力较小的一个攻击
        if (L < 1)
            target = R++;
        else if (R > n)
            target = L--;
        else if (a[L] <= a[R])
            target = L--;
        else
            target = R++;

        if (current_atk < a[target]) {
            start_atk += (a[target] - current_atk);
            current_atk = a[target];
        }
        current_atk += b[target];
    }
    return start_atk;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<ll> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    vector<ll> a_bak = a, b_bak = b;  // 备份用于还原
    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        while (k--) {
            int idx;
            ll va, vb;
            cin >> idx >> va >> vb;
            a[idx] = va;
            b[idx] = vb;
        }

        ll ans = 0;
        for (int i = 1; i < n; i++) ans ^= get_p(i, n, a, b);
        cout << ans << "\n";

        a = a_bak;
        b = b_bak;  // 还原数据
    }
    return 0;
}
/*
#include <iostream>
#include <vector>

using namespace std;

void getMaxInfo(int& maxDay, int& maxIndex, vector<vector<int>>& field) {
    for (int i = 0; i < field.size(); i++) {
        if (field[i][0] >= maxDay) {
            maxDay = field[i][0];
            maxIndex = i;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> field(n, vector<int>(2, 0));
    for (int i = 0; i < n; i++) {
        int ti, ci;
        cin >> field[i][0] >> field[i][1];
    }

    int maxDay = 0, maxIndex = 0;
    getMaxInfo(maxDay, maxIndex, field);

    while (m > 0 && maxDay >= k) {
        maxDay = 0;
        getMaxInfo(maxDay, maxIndex, field);
        if (m < field[maxIndex][1]) {
            break;
        }
        field[maxIndex][0]--;
        m -= field[maxIndex][1];
    }

    maxDay = 0;
    getMaxInfo(maxDay, maxIndex, field);

    cout << maxDay << endl;
}

*/

/*
4 9 2
6 1
5 1
6 2
7 1
*/

/*
如果三根柱子高度分别是 `[7, 7, 5]`，资源单价分别是 `[1, 2, 1]`。
1.  **你的逻辑：** 看到第一根 7 最高，锯掉 1 米（花 1 元），高度变成 `[6, 7, 5]`。此时总高度还是
**7**（第二根拖了后腿）。
2.  **二分的逻辑：** 它不关心你是怎么锯的。它直接问：“我想把总高度降到 **5** 米，行不行？”
    * 第一根：从 7 降到 5，需要锯 2 米，花 $2 \times 1 = 2$ 元。
    * 第二根：从 7 降到 5，需要锯 2 米，花 $2 \times 2 = 4$ 元。
    * 第三根：已经是 5 了，不用锯。
    * **结论：** 总共要花 $2 + 4 = 6$ 元。如果你的钱 $m \ge 6$，那“降到 5 米”这个目标就**可行**。


### 程序的执行步骤：
1.  **猜一个中间值 `mid`**（比如当前范围是 2 到 100 天，我们就猜 51 天）。
2.  **验证 `mid` 行不行**：
    * 遍历一遍所有区域。
    * 只要某个区域耗时 $t_i > mid$，就计算把这块区域缩减到 $mid$ 天要花多少钱：$(t_i - mid) \times c_i$。
    * 把所有这些钱加起来，看是否 $\le$ 你手里的 $m$。
3.  **调整范围**：
    * 如果**行**：说明 `mid` 天可以实现。但这不一定是最小的，我们尝试更小的天数，把范围缩小到 $[k, mid-1]$。
    * 如果**不行**：说明钱不够，`mid` 天做不到。我们必须增加天数，把范围缩小到 $[mid+1, \text{max}(t_i)]$。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

// 检查在 targetDay 天内完成，资源 m 是否够用
bool check(int targetDay, int n, ll m, const vector<pair<int, int>>& fields) {
    ll totalCost = 0;
    for (int i = 0; i < n; i++) {
        if (fields[i].first > targetDay) {
            // 需要缩减的天数 = 原天数 - 目标天数
            // 总消耗 = 天数 * 资源单价
            totalCost += (ll)(fields[i].first - targetDay) * fields[i].second;
        }
    }
    return totalCost <= m;
}

int main() {
    int n, k;
    ll m;
    if (!(cin >> n >> m >> k)) return 0;

    vector<pair<int, int>> fields(n);
    int maxT = 0;
    for (int i = 0; i < n; i++) {
        cin >> fields[i].first >> fields[i].second;
        maxT = max(maxT, fields[i].first);
    }

    int left = k, right = maxT, ans = maxT;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid, n, m, fields)) {
            ans = mid;  // 这个天数行，试试能不能更短
            right = mid - 1;
        } else {
            left = mid + 1;  // 资源不够，只能天数长一点
        }
    }

    cout << ans << endl;
    return 0;
}
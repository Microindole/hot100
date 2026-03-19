### 基础 Dijkstra 模板（无结构体版）

在这个版本中，我们用 `-1` 代表“无穷大”，逻辑判断会稍微多一点点，但胜在不需要记 `0x3f3f3f3f`。

```cpp
#include <iostream>
#include <vector>

using namespace std;

// n: 点数, m: 边数, start: 起点
void basicDijkstra(int n, int m, int start) {
    // 1. 存储图：用两个 vector 数组代替结构体
    // to[u][i] 表示从 u 出发的第 i 条边的终点
    // val[u][i] 表示从 u 出发的第 i 条边的权重
    vector<vector<int>> to(n + 1);
    vector<vector<int>> val(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        to[u].push_back(v);
        val[u].push_back(w);
    }

    // 2. 初始化：dist 为 -1 表示无穷大
    vector<int> dist(n + 1, -1); 
    vector<bool> vis(n + 1, false);

    dist[start] = 0;

    // 3. 核心循环：执行 n 次，每次确定一个点的最短路径
    for (int i = 1; i <= n; i++) {
        int u = -1;

        // 步骤 A：找当前未访问过的、距离起点最近的点 u
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dist[j] != -1) {
                if (u == -1 || dist[j] < dist[u]) {
                    u = j;
                }
            }
        }

        // 如果找不到可达的点（剩下的点都连不通），直接退出
        if (u == -1) break;

        // 步骤 B：标记 u 为已确定
        vis[u] = true;

        // 步骤 C：更新 u 的所有邻居
        for (int j = 0; j < to[u].size(); j++) {
            int v = to[u][j];
            int w = val[u][j];

            // 如果 v 之前没到过 (-1)，或者通过 u 走更近
            if (dist[v] == -1 || dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // 4. 输出结果
    for (int i = 1; i <= n; i++) {
        if (dist[i] == -1) cout << "点 " << i << " 不可达" << endl;
        else cout << "到点 " << i << " 的最短距离: " << dist[i] << endl;
    }
}

int main() {
    int n, m, start;
    if (cin >> n >> m >> start) {
        basicDijkstra(n, m, start);
    }
    return 0;
}
```



---

### 为什么这样写在考场上有优势？

1.  **避开溢出风险**：新手常用 `9999999` 当无穷大，但如果两条边一加就会溢出成负数。用 `-1` 配合 `dist[v] == -1` 的判断，物理意义明确且绝对不会溢出。
2.  **不依赖复杂语法**：没有 `pair`，没有 `struct`，没有 `priority_queue`。只要会 `vector` 和 `for` 循环就能写出来。
3.  **调试方便**：如果你发现输出不对，直接 `cout` 每个点的 `dist` 状态，`-1` 一眼就能看出哪些点还没被搜到。

### 考前提点：

* **双向图**：如果题目说“无向图”，记得 `u` 连 `v` 的时候，`v` 也要连一遍 `u`。
* **点号**：注意题目是从 0 开始编号还是从 1 开始。上面的代码是从 1 开始的，如果是 0，把 `i <= n` 改成 `i < n` 即可。
* **自环与重边**：邻接表（`vector` 存边）天生支持重边和自环，不需要额外逻辑处理。

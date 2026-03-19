#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 使用 long long 防止延迟加总后超过 int 范围
typedef long long ll;
const ll INF = 1e18;

// 定义最大范围（根据题目要求调整，这里假设 n+m 最大 200,000）
const int MAXN = 200005;

// 基础数组
int node_x[MAXN], node_y[MAXN];
int st_x[MAXN], st_y[MAXN], st_r[MAXN], st_t[MAXN];

// 邻接表：e[u] 存储从 u 出发能到达的点，w[u] 存储对应的边权
vector<int> e[MAXN];
vector<ll> w[MAXN];

// Dijkstra 用到的数组
ll dist[MAXN];

int main() {
    int n, m;
    if (!(cin >> n >> m))
        return 0;

    // 1. 输入节点坐标
    for (int i = 1; i <= n; i++) {
        cin >> node_x[i] >> node_y[i];
    }

    // 2. 输入基站信息
    for (int i = 1; i <= m; i++) {
        cin >> st_x[i] >> st_y[i] >> st_r[i] >> st_t[i];
    }

    // 3. 建图 (核心：点与基站的相互连接)
    for (int j = 1; j <= m; j++) {
        int st_id = n + j;  // 给基站起个编号，从 n+1 开始
        for (int i = 1; i <= n; i++) {
            // 判断点 i 是否在基站 j 的范围内
            // abs(x1 - x2) <= r 且 abs(y1 - y2) <= r
            if (abs(node_x[i] - st_x[j]) <= st_r[j] &&
                abs(node_y[i] - st_y[j]) <= st_r[j]) {
                // 节点 -> 基站，权值为 st_t[j]
                e[i].push_back(st_id);
                w[i].push_back((ll)st_t[j]);

                // 基站 -> 节点，权值为 0
                e[st_id].push_back(i);
                w[st_id].push_back(0LL);
            }
        }
    }

    // 4. 标准 Dijkstra 算法
    for (int i = 1; i <= n + m; i++) dist[i] = INF;

    // 优先队列存的是 <距离, 点的编号>
    // pair<ll, int> 默认先按第一个元素（距离）排序
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
        pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        // 遍历 u 的所有邻居
        for (int i = 0; i < e[u].size(); i++) {
            int v = e[u][i];
            ll weight = w[u][i];
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // 5. 输出结果
    if (dist[n] == INF) {
        cout << "Nan" << endl;
    } else {
        cout << dist[n] << endl;
    }

    return 0;
}
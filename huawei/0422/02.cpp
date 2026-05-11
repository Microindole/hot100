#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// 用于存储原始输入的依赖关系，保证输出顺序
struct Dependency {
    long long u, v;
    int original_version;
};

void solve() {
    int n;
    if (!(cin >> n)) return;

    vector<Dependency> input_order;                   // 记录输入顺序
    unordered_map<long long, vector<long long>> adj;  // 邻接表
    unordered_map<long long, int> in_degree;  // 记录每个节点的入度
    unordered_map<long long, int> max_versions;  // 记录每个部件 v 的最大版本号
    unordered_set<long long> all_nodes;  // 统计所有出现的节点

    for (int i = 0; i < n; ++i) {
        string line;
        cin >> line;
        // 处理逗号分隔的字符串 "u,v,version"
        replace(line.begin(), line.end(), ',', ' ');
        stringstream ss(line);
        long long u, v;
        int ver;
        ss >> u >> v >> ver;

        // 1. 存储原始信息
        input_order.push_back({u, v, ver});

        // 2. 统计最大版本号：针对被依赖的对象 v
        if (max_versions.find(v) == max_versions.end() ||
            ver > max_versions[v]) {
            max_versions[v] = ver;
        }

        // 3. 构建图结构用于环检测
        adj[u].push_back(v);
        all_nodes.insert(u);
        all_nodes.insert(v);

        // 4. 维护入度
        in_degree[v]++;
        if (in_degree.find(u) == in_degree.end()) {
            in_degree[u] = 0;
        }
    }

    // --- 拓扑排序 (Kahn's Algorithm) ---
    queue<long long> q;
    for (long long node : all_nodes) {
        if (in_degree[node] == 0) {
            q.push(node);
        }
    }

    int visited_count = 0;
    while (!q.empty()) {
        long long curr = q.front();
        q.pop();
        visited_count++;

        if (adj.count(curr)) {
            for (long long neighbor : adj[curr]) {
                in_degree[neighbor]--;
                if (in_degree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
    }

    // --- 结果输出 ---
    // 如果处理过的节点数不等于总节点数，说明图中存在环
    if (visited_count != (int)all_nodes.size()) {
        cout << "false" << endl;
    } else {
        for (const auto& dep : input_order) {
            cout << dep.u << "," << dep.v << "," << max_versions[dep.v] << endl;
        }
    }
}

int main() {
    solve();
    solve();
    return 0;
}
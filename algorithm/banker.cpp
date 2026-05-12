#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 安全性检查函数：使用引用传递数据，避免拷贝
bool is_safe(int n, int m, vector<int> work, const vector<vector<int>>& need,
             const vector<vector<int>>& alloc) {
    vector<bool> finish(n, false);
    vector<int> safe_seq;

    for (int k = 0; k < n; ++k) {
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                // 检查当前进程 P_i 的资源需求是否能被满足
                bool can_exec = true;
                for (int j = 0; j < m; ++j) {
                    if (need[i][j] > work[j]) {
                        can_exec = false;
                        break;
                    }
                }

                if (can_exec) {
                    // 模拟运行完并回收已分配的资源
                    for (int j = 0; j < m; ++j) work[j] += alloc[i][j];
                    finish[i] = true;
                    safe_seq.push_back(i);
                    found = true;
                    break;
                }
            }
        }
        if (!found)
            break;
    }

    if (safe_seq.size() == n) {
        cout << "> 安全序列: ";
        for (int i = 0; i < n; ++i)
            cout << "P" << safe_seq[i] << (i == n - 1 ? "" : " -> ");
        cout << endl;
        return true;
    }
    return false;
}

int main() {
    // n是进程数，m是资源数
    int n, m;
    if (!(cin >> n >> m))
        return 0;

    // 动态分配大小，不预设大数组
    vector<int> avail(m);
    vector<vector<int>> max_d(n, vector<int>(m));
    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));

    for (int i = 0; i < m; ++i) cin >> avail[i];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> max_d[i][j];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> alloc[i][j];
            need[i][j] = max_d[i][j] - alloc[i][j];
        }
    }

    // 初始状态安全性检查
    if (!is_safe(n, m, avail, need, alloc)) {
        cout << "> 警告：初始状态不安全！" << endl;
    } else {
        cout << "> 初始状态安全。" << endl;
    }

    int p_idx;
    while (cout << "\n请求进程编号: " && cin >> p_idx) {
        vector<int> req(m);
        cout << "请求资源向量: ";
        for (int i = 0; i < m; ++i) cin >> req[i];

        // 校验请求合法性
        bool ok = true;
        for (int i = 0; i < m; ++i) {
            if (req[i] > need[p_idx][i] || req[i] > avail[i]) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            cout << "> 请求失败：超过需求量或系统资源不足。" << endl;
        } else {
            // 尝试性分配（修改局部变量）
            for (int i = 0; i < m; ++i) {
                avail[i] -= req[i];
                alloc[p_idx][i] += req[i];
                need[p_idx][i] -= req[i];
            }

            // 检查分配后是否安全
            if (is_safe(n, m, avail, need, alloc)) {
                cout << "> 成功：已批准分配。" << endl;
            } else {
                // 回滚
                for (int i = 0; i < m; ++i) {
                    avail[i] += req[i];
                    alloc[p_idx][i] -= req[i];
                    need[p_idx][i] += req[i];
                }
                cout << "> 拒绝：分配将导致系统进入不安全状态。" << endl;
            }
        }
    }

    return 0;
}
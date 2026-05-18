/**
 * 这题来自网易实习生笔试
 * 大意是，编译项目时有依赖关系，比如编译 b 要 a 编译好后才能继续 (可以使用 CPU
 * 多线程加速编译) 现在有 n 个项目， k 个依赖关系，每个项目耗时 w[i]，
 * 计算在双线程 CPU 下最短编译时间 (无法编译(循环依赖)则返回 -1)
 * 0 <= n, k <= 1000, 这里规定 w[i] 不会越界
 */

/**
 * 这个版本是我当时做的
 * 这里只考虑了多线程的情况，并不是双线程
 * 下面才是正确答案
 *
 * #include <algorithm>
 * #include <iostream>
 * #include <queue>
 * #include <unordered_map>
 * #include <vector>
 *
 * using namespace std;
 *
 * int getCost(vector<int>& w, vector<vector<bool>>& depend, vector<int>& du) {
 *     queue<int> q;
 *     unordered_map<int, int> eachCost;
 *
 *     /// int thread1 = 0, thread2 = 0;
 *     int timeCursor = 0;
 *
 *     int signal = 0;
 *
 *     for (int i = 0; i < du.size(); i++) {
 *         if (du[i] == 0) {
 *             q.push(i);
 *
 *             eachCost[i] = w[i];
 *         }
 *     }
 *
 *     while (!q.empty()) {
 *         int front = q.front();
 *         q.pop();
 *
 *         for (int i = 0; i < depend[front].size(); i++) {
 *             if (depend[front][i]) {
 *                 du[i]--;
 *                 if (du[i] == 0) {
 *                     q.push(i);
 *
 *                     int maxTemp = 0;
 *                     for (int j = 0; j < depend.size(); j++) {
 *                         if (depend[j][i]) {
 *                             maxTemp = max(maxTemp, eachCost[j]);
 *                         }
 *                     }
 *
 *                     eachCost[i] = maxTemp + w[i];
 *                 }
 *             }
 *         }
 *     }
 *
 *     if (eachCost.size() == depend.size()) {
 *         int cost = 0;
 *
 *         for (auto const& [key, value] : eachCost) {
 *             cost = max(cost, value);
 *         }
 *
 *         return cost;
 *     }
 *     return -1;
 * }
 *
 * int main() {
 *     int n, k;
 *     cin >> n >> k;
 *
 *     vector<int> w(n, 0);
 *     for (int i = 0; i < n; i++) {
 *         cin >> w[i];
 *     }
 *
 *     vector<vector<bool>> depend(n, vector<bool>(n, false));
 *     vector<int> du(n, 0);
 *
 *     /// 0 1
 *     /// 0 2
 *     /// 1 3
 *     /// 2 3
 *     ///
 *     /// 0 0 0 0
 *     /// 1 0 0 0
 *     /// 1 0 0 0
 *     /// 0 1 0 1
 *
 *     for (int i = 0; i < k; i++) {
 *         int x, y;
 *         cin >> x >> y;
 *         depend[y - 1][x - 1] = true;
 *
 *         du[x - 1]++;
 *     }
 *
 *     cout << getCost(w, depend, du) << endl;
 * }
 *
 *
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * @brief 计算双线程 CPU 条件下的最快项目编译总耗时（带依赖拓扑调度）
 *
 * @details
 * 本算法采用基于“时间指针跃迁”的动态扫描线思想，利用优先队列（小根堆）
 * 模拟双核 CPU 的任务分发与限流排队过程。
 *
 * 【算法核心数据流与决策示意图】
 *  +---------------------------------------------------------------+
 *  | 初始状态: 遍历 du, 将所有 du[i] == 0 的项目以 {0, i} 压入堆 q |
 *  +---------------------------------------------------------------+
 *                                 │
 *                                 ▼
 *                    q (小根堆, 按 readyTime 排序)
 *                    ┌─────────────────────────┐
 *                    │  {t0, idA}, {t1, idB}   │
 *                    └────────────┬────────────┘
 *                                 │ 弹出当前最早可执行任务
 *                                 ▼
 *             startTime = max(readyTime, min(thread1, thread2))
 *                                 │
 *                ┌────────────────┴────────────────┐ 贪心分配线程
 *                ▼                                 ▼
 *        [Thread 1 (thread1)]              [Thread 2 (thread2)]
 *        更新 thread1 =                    更新 thread2 =
 *        startTime + w[front]              startTime + w[front]
 *                │                                 │
 *                └────────────────┬────────────────┘ 任务完工
 *                                 ▼
 *       记录 eachCost[front], 遍历后继节点并递减其入度
 *       若后继节点 i 入度清零 -> 联动计算 maxTemp -> 重新压入堆 q
 *
 * @param w 节点权重数组，w[i] 表示编译项目 i 所需的时间。
 * @param depend 邻接矩阵，depend[y][x] == true 表示 y 是 x 的前置依赖。
 * @param du 入度数组，du[i] 表示项目 i 当前未解锁的前置依赖数量。
 * @return int 返回完成编译的总时间；若存在循环依赖导致无法编译则返回 -1。
 */
int getCost(vector<int>& w, vector<vector<bool>>& depend, vector<int>& du) {
    // 把 queue 改为 priority_queue（小根堆），里面存的是
    // {最早可开始时间, 项目编号}
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        q;
    unordered_map<int, int> eachCost;

    // 【修改 2】把原本注释掉的两个线程变量启用，代表两个 CPU
    // 线程当前完工的时间点
    int thread1 = 0, thread2 = 0;
    int timeCursor = 0;

    int signal = 0;

    for (int i = 0; i < du.size(); i++) {
        if (du[i] == 0) {
            // 【修改 3】入度为 0 的项目，最早可开始时间是 0
            q.push({0, i});

            // 注意：这里不要直接算 eachCost[i] 了，等它出队上 CPU 时再统一算
        }
    }

    while (!q.empty()) {
        // 优先队列用 top() 取出当前最早可以开始编译的项目
        auto [readyTime, front] = q.top();
        q.pop();

        // 核心限流逻辑：
        // 这一步决定了项目什么时候真正开始编译：取决于【它自己准备好的时间】和【两个线程中最早空闲的那个时间】的最大值
        int startTime = max(readyTime, min(thread1, thread2));
        eachCost[front] =
            startTime + w[front];  // 实际完工时间 = 开始时间 + 自身耗时

        // 更新派发了该任务的那个线程的空闲时间
        if (thread1 <= thread2) {
            thread1 = eachCost[front];
        } else {
            thread2 = eachCost[front];
        }

        for (int i = 0; i < depend[front].size(); i++) {
            if (depend[front][i]) {
                du[i]--;
                if (du[i] == 0) {
                    int maxTemp = 0;
                    for (int j = 0; j < depend.size(); j++) {
                        if (depend[j][i]) {
                            maxTemp = max(maxTemp, eachCost[j]);
                        }
                    }

                    // 项目 i 的前置依赖都完了，它在 maxTemp
                    // 时刻具备了编译资格，送去排队
                    q.push({maxTemp, i});
                }
            }
        }
    }

    if (eachCost.size() == depend.size()) {
        int cost = 0;

        for (auto const& [key, value] : eachCost) {
            cost = max(cost, value);
        }

        return cost;
    }
    return -1;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> w(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    vector<vector<bool>> depend(n, vector<bool>(n, false));
    vector<int> du(n, 0);

    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        depend[y - 1][x - 1] = true;

        du[x - 1]++;
    }

    cout << getCost(w, depend, du) << endl;
}
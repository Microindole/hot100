/**
 * 这题来自网易实习生笔试
 * 大意是，编译项目时有依赖关系，比如编译 b 要 a 编译好后才能继续 (可以使用 CPU
 * 多线程加速编译) 现在有 n 个项目， k 个依赖关系，计算在双线程 CPU
 * 下最短编译时间 (无法编译(循环依赖)则返回 -1)
 */

/**
 * 这个版本是我当时做的，下面是正确答案
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
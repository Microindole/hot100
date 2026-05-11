#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 建议在考场上直接定义数组，比 vector 更快且省事
int p[105], t[105];
int early[105], late[105];

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 1. 读取依赖关系 (p_i) 和 训练耗时 (t_i)
    for (int i = 1; i <= m; i++) cin >> p[i];
    for (int i = 1; i <= m; i++) cin >> t[i];

    // 2. 正向遍历：计算“最早开始时间”
    bool can_finish_all = true;
    for (int i = 1; i <= m; i++) {
        if (p[i] == 0) {
            early[i] = 1;  // 无依赖，从第 1 天开始
        } else {
            // 最早开始时间 = 依赖项的最早开始时间 + 依赖项的耗时
            early[i] = early[p[i]] + t[p[i]];
        }
        // 检查第 i 项是否会超出总期限 n
        if (early[i] + t[i] - 1 > n) {
            can_finish_all = false;
        }
    }

    // 输出第一行结果
    for (int i = 1; i <= m; i++) {
        cout << early[i] << (i == m ? "" : " ");
    }
    cout << endl;

    // 3. 逆向遍历：计算“最晚开始时间”
    if (can_finish_all) {
        // 首先初始化为：在不考虑被依赖的情况下，最晚可以开始的时间
        for (int i = 1; i <= m; i++) {
            late[i] = n - t[i] + 1;
        }

        // 从后往前更新：被依赖项的最晚时间，取决于依赖它的所有项
        for (int i = m; i >= 1; i--) {
            if (p[i] != 0) {
                // 如果科目 i 依赖科目 p[i]
                // 那么 p[i] 必须在 i 开始前完成
                // 即 p[i] 的最晚开始时间，不能超过 (i 的最晚开始时间 - p[i]
                // 的耗时)
                late[p[i]] = min(late[p[i]], late[i] - t[p[i]]);
            }
        }

        // 输出第二行结果
        for (int i = 1; i <= m; i++) {
            cout << late[i] << (i == m ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}
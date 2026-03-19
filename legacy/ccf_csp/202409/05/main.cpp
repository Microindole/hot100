/*
 *  木板切割
 */

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> c(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        cin >> c[1][i];
    }

    for (int i = 1; i <= k; i++) {
        int x, l, r;
        cin >> x >> l >> r;

        unordered_set<int> clr;

        int temp = 0;
        int res = 0;

        for (int j = l; j <= r; j++) {
            c[i + 1][j] = c[x][j];

            if (c[x][j] != 0) {
                clr.insert(c[x][j]);
            }

            if (temp != c[x][j] && c[x][j] != 0) {
                temp = c[x][j];
                res++;
            }
            c[x][j] = 0;
        }

        cout << clr.size() << " " << res << "\n";
    }
    return 0;
}

/**
 * 稍微优化了一下内存
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 1. 内存优化：全局数组
int initial_color[100005];
set<int> board[100005]; // board[i] 存储 i 号木板当前拥有的所有段落编号

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> initial_color[i];
        board[1].insert(i); // 初始都在 1 号木板
    }

    for (int i = 1; i <= k; i++) {
        int x, l, r;
        cin >> x >> l >> r;

        unordered_set<int> clr_types;
        int res = 0;
        int temp = 0;

        // 2. 策略优化：只遍历木板 x 中编号在 [l, r] 之间的段
        auto it = board[x].lower_bound(l);
        vector<int> to_move; // 暂存要切走的编号

        while (it != board[x].end() && *it <= r) {
            int segment_id = *it;
            int c = initial_color[segment_id];

            // 你的逻辑：统计不同颜色
            clr_types.insert(c);

            // 你的逻辑：统计颜色段
            if (temp != c) {
                temp = c;
                res++;
            }

            to_move.push_back(segment_id);
            it++; // 迭代器向后移
        }

        // 3. 执行物理切割
        for (int id : to_move) {
            board[x].erase(id);
            board[i + 1].insert(id);
        }

        // 4. 输出
        if (to_move.empty()) {
            cout << "0 0\n";
        } else {
            cout << clr_types.size() << " " << res << "\n";
        }
    }

    return 0;
}
 */
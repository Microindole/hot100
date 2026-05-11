#include <algorithm>
#include <climits>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

// 随机层数函数
int randomLevel(int max_level) {
    int l = 1;
    while (rand() % 2 && l < max_level) l++;
    return l;
}

// 插入函数：通过引用传递 vals 和 nexts
void insert(int x, vector<int>& vals, vector<vector<int>>& nexts,
            int& cur_level, int max_level) {
    int head = 0;
    vector<int> update(max_level, head);
    int p = head;

    // 1. 寻找每一层的前驱
    for (int i = cur_level - 1; i >= 0; i--) {
        while (nexts[p][i] != -1 && vals[nexts[p][i]] < x) {
            p = nexts[p][i];
        }
        update[i] = p;
    }

    int l = randomLevel(max_level);
    cur_level = max(cur_level, l);

    // 2. 动态分配新下标
    int now = vals.size();
    vals.push_back(x);
    nexts.push_back(vector<int>(l, -1));

    // 3. 更新指针
    for (int i = 0; i < l; i++) {
        nexts[now][i] = nexts[update[i]][i];
        nexts[update[i]][i] = now;
    }
}

// 查找函数
bool search(int x, const vector<int>& vals, const vector<vector<int>>& nexts,
            int cur_level) {
    int p = 0;  // head 始终是 0
    for (int i = cur_level - 1; i >= 0; i--) {
        while (nexts[p][i] != -1 && vals[nexts[p][i]] < x) {
            p = nexts[p][i];
        }
    }
    p = nexts[p][0];
    return p != -1 && vals[p] == x;
}

// 删除函数
bool remove(int x, const vector<int>& vals, vector<vector<int>>& nexts,
            int& cur_level, int max_level) {
    int head = 0;
    vector<int> update(max_level, head);
    int p = head;

    for (int i = cur_level - 1; i >= 0; i--) {
        while (nexts[p][i] != -1 && vals[nexts[p][i]] < x) {
            p = nexts[p][i];
        }
        update[i] = p;
    }

    int target = nexts[p][0];
    if (target == -1 || vals[target] != x) return false;

    for (int i = 0; i < cur_level; i++) {
        if (nexts[update[i]][i] != target) break;
        nexts[update[i]][i] = nexts[target][i];
    }

    // 维护当前层数
    while (cur_level > 1 && nexts[head][cur_level - 1] == -1) {
        cur_level--;
    }
    return true;
}

int main() {
    // 快速 IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));

    // 局部变量管理状态，不使用全局变量
    const int MAX_L = 16;
    int cur_level = 1;

    // 核心容器：vals 存值，nexts[i][j] 存第 i 个节点在第 j 层的下游下标
    vector<int> vals;
    vector<vector<int>> nexts;

    // 初始化头节点（哨兵）
    vals.push_back(INT_MIN);
    nexts.push_back(vector<int>(MAX_L, -1));

    // 测试插入
    insert(10, vals, nexts, cur_level, MAX_L);
    insert(20, vals, nexts, cur_level, MAX_L);
    insert(5, vals, nexts, cur_level, MAX_L);

    // 测试查找
    if (search(10, vals, nexts, cur_level)) cout << "Found 10" << endl;

    // 测试删除
    if (remove(10, vals, nexts, cur_level, MAX_L)) cout << "Deleted 10" << endl;

    if (!search(10, vals, nexts, cur_level)) cout << "10 is gone" << endl;

    return 0;
}
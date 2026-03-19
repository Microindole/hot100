#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<bool> flag(n + 1, false);
    vector<int> a(m);

    for (int i = 0; i < m; i++) {
        cin >> a[i];
        flag[a[i]] = true;
    }

    // 第一步：降序输出比 a[0] 大且不在 LIS 里的数
    // 这样做是为了让这些大数挡在前面，不跟后面的数形成上升序列
    for (int i = n; i >= 1; i--) {
        if (!flag[i] && i > a[0]) {
            cout << i << " ";
        }
    }

    // 第二步：输出题目给定的 LIS
    for (int i = 0; i < m; i++) {
        cout << a[i] << " ";
    }

    // 第三步：降序输出比 a[0] 小且不在 LIS 里的数
    // 这样做是为了让这些小数在最后，无法延长 a[m-1]
    for (int i = n; i >= 1; i--) {
        if (!flag[i] && i < a[0]) {
            cout << i << " ";
        }
    }

    cout << endl;
    return 0;
}
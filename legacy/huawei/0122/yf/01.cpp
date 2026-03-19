/**
 * 前缀和解法
 */

/*
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n, 0), pa(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pa[i + 1] = pa[i] + a[i];
    }

    int minp = pa[0];
    int res = 0;

    for (int i = 1; i <= n; i++) {
        if (pa[i] < minp) {
            minp = pa[i];
        }

        int temp = pa[i] - minp;

        if (temp > res) {
            res = temp;
        }
    }

    cout << res;

    return 0;
}

*/

/**
 * 动态规划解法
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long curr = a[0];
    long long res = a[0];

    for (int i = 1; i < n; i++) {
        curr = max((long long)a[i], curr + a[i]);
        res = max(curr, res);
    }

    cout << res;

    return 0;
}
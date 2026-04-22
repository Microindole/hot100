#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    pair<int, int> node;
    priority_queue<pair<int, int>> p;

    for (int i = 0; i < n; i++) {
        node.second = i;
        node.first = a[i] - max((a[i] + 1) / 2, b[i]);

        p.push(node);
    }

    for (int i = 0; i < m; i++) {
        node = p.top();
        p.pop();

        int num = node.second;

        if (node.first <= 0) {
            break;
        }

        a[num] -= node.first;

        node.first = a[num] - max((a[num] + 1) / 2, b[num]);

        p.push(node);
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        res += a[i];
    }

    cout << res;

    return 0;
}
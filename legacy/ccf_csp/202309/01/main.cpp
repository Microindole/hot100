#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        int dx, dy;
        cin >> dx >> dy;
        x += dx;
        y += dy;
    }

    vector<vector<int>> res(m, vector<int>(2, 0));
    for (int i = 0; i < m; i++) {
        int xi, yi;
        cin >> xi >> yi;
        res[i][0] = xi + x;
        res[i][1] = yi + y;
    }

    for (int i = 0; i < m; i++) {
        cout << res[i][0] << " " << res[i][1] << "\n";
    }

    return 0;
}

/*
3 2
10 10
0 0
10 -20
1 -1
0 0
*/
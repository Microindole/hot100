#include <iostream>
#include <vector>

using namespace std;

void performTranspose(vector<int>& src, int& n, int& m) {
    vector<int> next(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            next[j * n + i] = src[i * m + j];
        }
    }
    src = next;
    swap(n, m);
}

int getValue(int x, int y, vector<int>& src, int ysize) { return src[x * ysize + y]; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, t;
    cin >> n >> m >> t;
    vector<int> src(n * m, 0);
    for (int i = 0; i < m * n; i++) {
        cin >> src[i];
    }

    vector<vector<int>> cmd(t, vector<int>(3, 3));
    for (int i = 0; i < t; i++) {
        cin >> cmd[i][0] >> cmd[i][1] >> cmd[i][2];
    }

    for (int i = 0; i < t; i++) {
        if (cmd[i][0] == 2) {
            performTranspose(src, n, m);
        } else if (cmd[i][0] == 1) {
            n = cmd[i][1];
            m = cmd[i][2];
        } else {
            cout << getValue(cmd[i][1], cmd[i][2], src, m) << "\n";
        }
    }

    return 0;
}

/*
3 2 3
1 2
3 4
5 6
3 0 1
1 2 3
3 1 2

3 2 5
1 2
3 4
5 6
3 1 0
2 0 0
3 1 0
1 3 2
3 1 0
*/
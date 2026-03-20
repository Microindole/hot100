#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, p, q;
    cin >> n >> m >> p >> q;
    if (n * m != p * q) return 0;

    vector<vector<int>> src(n, vector<int>(m, 0)), pos(p, vector<int>(q, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> src[i][j];
        }
    }

    int ptemp = 0, qtemp = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pos[ptemp][qtemp] = src[i][j];
            qtemp++;
            if (qtemp == q) {
                qtemp = 0;
                ptemp++;
            }
        }
    }

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            cout << pos[i][j] << (j == (q - 1) ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}

// 其实连 src 矩阵都不用存，直接读一个输出一个

/*
2 3 3 2
1 2 3
4 5 6

2 2 1 4
6 6
6 6
*/
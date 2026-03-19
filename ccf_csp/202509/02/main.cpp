#include <bits/stdc++.h>

using namespace std;

void getMaxAndMin(int &max, int &min, const vector<vector<int>> &mat, int x, int y, vector<vector<int>> isCSP, int L) {
    max = -1;
    min = L;
    int index = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            if (index < isCSP.size() && isCSP[index][0] == i && isCSP[index][1] == j) {
                if (mat[x + i][y + j] <= min) {
                    min = mat[x + i][y + j];
                }
                index++;
            } else {
                if (mat[x + i][y + j] > max) {
                    max = mat[x + i][y + j];
                }
            }
        }
    }
}
// (max, min]
int main() {
    const vector<vector<int>> isCSP = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {1, 0},
                                       {1, 3}, {1, 6}, {1, 8}, {2, 0}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {3, 0},
                                       {3, 5}, {3, 6}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}};
    int n, L;
    cin >> n >> L;
    int max = -1, min = L;
    vector<vector<int>> mat(n, vector<int>(n, 0));
    vector<int> res(L + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }
    for (int i = 0; i <= n - 5; i++) {
        for (int j = 0; j <= n - 9; j++) {
            getMaxAndMin(max, min, mat, i, j, isCSP, L);
            if (max <= min) {
                for (int index = max + 1; index <= min; index++) {
                    res[index]++;
                }
            }
        }
    }
    for (int i = 0; i < res.size(); i++) {
        if (res[i] > 0) {
            cout << i << endl;
        }
    }
    return 0;
}
/*
9 256
9 9 8 8 9 9 9 8 255
9 0 0 8 0 0 7 0 8
9 0 0 8 7 9 7 7 5
9 0 0 0 0 8 7 0 0
7 7 8 7 7 8 8 6 5
6 2 2 5 1 1 5 1 6
6 2 2 6 6 6 7 5 3
6 2 2 2 1 5 8 1 1
7 7 8 7 7 8 8 2 3
*/
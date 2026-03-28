#include <iostream>
#include <set>
#include <vector>

using namespace std;

int mex(set<int>& hasValue) {
    int i = 0;
    for (int x : hasValue) {
        if (x != i) {
            return i;
        }
        i++;
    }
    return i;
}

bool getSet(int x, int y, set<int>& hasValue, vector<vector<bool>>& mat, vector<int>& value) {
    if (x == y) {
        return true;
    }
    for (int i = 1; i < mat.size(); i++) {
        if (mat[x][i]) {
            mat[x][i] = false;
            mat[i][x] = false;
            hasValue.insert(value[i]);

            if (getSet(i, y, hasValue, mat, value)) {
                mat[x][i] = true;
                mat[i][x] = true;
                return true;
            }

            hasValue.erase(value[i]);

            mat[x][i] = true;
            mat[i][x] = true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> value(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> value[i];
    }

    vector<vector<bool>> mat(n + 1, vector<bool>(n + 1, false));
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        mat[a][b] = true;
        mat[b][a] = true;
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        set<int> hasValue;
        hasValue.insert(value[x]);
        if (getSet(x, y, hasValue, mat, value)) {
            cout << mex(hasValue) << "\n";
        }
    }

    return 0;
}

/*
7 3
1 0 2 6 3 4 5
1 2
2 5
2 6
1 3
3 7
1 4
5 3
6 3
7 4
*/
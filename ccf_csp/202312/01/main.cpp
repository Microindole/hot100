#include <iostream>
#include <vector>

using namespace std;

int getUpRep(int pos, vector<vector<int>>& rep) {
    int res = 0;

    for (int i = 0; i < rep.size(); i++) {
        if (i == pos) {
            continue;
        }
        bool flag = true;
        for (int j = 0; j < rep[0].size(); j++) {
            if (rep[i][j] <= rep[pos][j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            res = i + 1;
            break;
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> rep(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> rep[i][j];
        }
    }

    for (int j = 0; j < n; j++) {
        cout << getUpRep(j, rep) << "\n";
    }

    return 0;
}

/*
4 2
0 0
-1 -1
1 2
0 -1
*/
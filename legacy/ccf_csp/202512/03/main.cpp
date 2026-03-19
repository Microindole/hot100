#include <iostream>
#include <string>
#include <vector>

using namespace std;

void nifanzhuan(int u, int d, int l, int r, int o, vector<vector<char>>& at) {
    if (o == 1) {
        while (u < d) {
            for (int i = l; i <= r; i++) {
                char temp = at[u][i];
                at[u][i] = at[d][i];
                at[d][i] = temp;
            }
            u++;
            d--;
        }

    } else {
        while (l < r) {
            for (int i = u; i <= d; i++) {
                char temp = at[i][l];
                at[i][l] = at[i][r];
                at[i][r] = temp;
            }
            l++;
            r--;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int z;
    cin >> z;

    vector<vector<char>> at(z, vector<char>(z, '\0'));
    for (int i = 0; i < z; i++) {
        for (int j = 0; j < z; j++) {
            cin >> at[i][j];
        }
    }

    int kLength;
    cin >> kLength;

    vector<int> k(kLength, 0);
    for (int i = 0; i < kLength; i++) {
        cin >> k[i];
    }

    int n = 0, m = 0;

    int processTimes = k[0];
    for (int i = processTimes; i > 0; i--) {
        int op = k[(i - 1) * 6 + 1];
        if (op == 2) {
            int u = k[(i - 1) * 6 + 2] - 1;
            int d = k[(i - 1) * 6 + 3] - 1;
            int l = k[(i - 1) * 6 + 4] - 1;
            int r = k[(i - 1) * 6 + 5] - 1;
            int o = k[(i - 1) * 6 + 6];
            nifanzhuan(u, d, l, r, o, at);
        }
    }

    for (int i = 0; i < z; i++) {
        if (at[i][0] != '?') {
            n++;
        }
    }

    for (int i = 0; i < z; i++) {
        if (at[0][i] != '?') {
            m++;
        }
    }

    cout << n << " " << m << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << at[i][j];
        }
        cout << "\n";
    }

    return 0;
}

/*
4
ccf?
?knl
????
????
7
1 2 2 3 1 4 -1
*/
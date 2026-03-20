#include <bits/stdc++.h>

using namespace std;

void getHangLie(int &hang, int &lie, int u, int delta, int n) {
    double res = (double)(n - u) / delta;
    int scaled = round(res * 100.0);
    hang = scaled / 10 + 1;
    lie = scaled % 10 + 1;
}

int main() {
    int hang = 0, lie = 0;
    int k;
    cin >> k;
    vector<vector<int>> res(k, vector<int>(3, 0));
    for (int i = 0; i < k; i++) {
        cin >> res[i][0] >> res[i][1] >> res[i][2];
    }
    for (int i = 0; i < k; i++) {
        getHangLie(hang, lie, res[i][0], res[i][1], res[i][2]);
        cout << hang << " " << lie << " " << endl;
    }
    return 0;
}

/*
4
0 1 1
2 10 127
2 50 2274
0 1 1
2 10 127
2 50 227
5 100 350
*/
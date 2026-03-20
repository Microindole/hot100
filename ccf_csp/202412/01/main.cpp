#include <iostream>
#include <string>
#include <vector>

using namespace std;

void move(int &x, int &y, char cmd, int n) {
    if (cmd == 'f') {
        if (y + 1 < n) {
            y += 1;
        }
    }
    if (cmd == 'b') {
        if (y - 1 >= 0) {
            y -= 1;
        }
    }
    if (cmd == 'l') {
        if (x - 1 >= 0) {
            x -= 1;
        }
    }
    if (cmd == 'r') {
        if (x + 1 < n) {
            x += 1;
        }
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> p(k, vector<int>(2, 0));
    vector<string> cmd_string(k, "");

    for (int i = 0; i < k; i++) {
        cin >> p[i][0] >> p[i][1] >> cmd_string[i];
        p[i][0]--;
        p[i][1]--;
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < (cmd_string[i]).size(); j++) {
            move(p[i][0], p[i][1], cmd_string[i][j], n);
        }
    }
    for (int i = 0; i < k; i++) {
        cout << p[i][0] + 1 << " " << p[i][1] + 1 << endl;
    }
}

/*
3 2
1 1 ffrrbbll
3 3 frbl

*/
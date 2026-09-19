#include <iostream>
#include <vector>

using namespace std;

bool goWay(int& x, int& y, vector<vector<char>>& grid, char way) {
    if (way == 'L') {
        if (y == 0) {
            return false;
        }

        y--;

    } else if (way == 'R') {
        if (y == grid[0].size() - 1) {
            return false;
        }
        y++;
    } else if (way == 'U') {
        if (x == 0) {
            return false;
        }

        x--;
    } else if (way == 'D') {
        if (x == grid.size() - 1) {
            return false;
        }

        x++;
    }

    return true;
}

void changeWay(char& way, char& mirror) {
    if (mirror == '/') {
        if (way == 'L') {
            way = 'D';
        } else if (way == 'R') {
            way = 'U';
        } else if (way == 'U') {
            way = 'R';
        } else {
            way = 'L';
        }
    } else {
        if (way == 'L') {
            way = 'U';
        } else if (way == 'R') {
            way = 'D';
        } else if (way == 'U') {
            way = 'L';
        } else {
            way = 'R';
        }
    }
}

void caluateLight(int x, int y, vector<vector<char>>& grid,
                  vector<vector<int>>& res) {
    char way = grid[x][y];

    while (goWay(x, y, grid, way)) {
        char ch = grid[x][y];

        if (ch == 'U' || ch == 'D' || ch == 'L' || ch == 'R' || ch == '#') {
            break;
        } else if (ch == '/' || ch == '\\') {
            changeWay(way, ch);
        } else {
            res[x][y]++;
        }
    }
}

int main() {
    int m, n;
    cin >> m >> n;

    vector<vector<char>> grid(m, vector<char>(n, '\0'));
    vector<vector<int>> res(m, vector<int>(n, 0));

    vector<pair<int, int>> done;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char ch;

            cin >> ch;

            grid[i][j] = ch;

            if (ch == '/' || ch == '\\' || ch == '#') {
                res[i][j] = -1;
            }

            else if (ch == 'L' || ch == 'R' || ch == 'U' || ch == 'D') {
                res[i][j] = -1;

                done.push_back({i, j});
            }
        }
    }

    for (int i = 0; i < done.size(); i++) {
        caluateLight(done[i].first, done[i].second, grid, res);
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
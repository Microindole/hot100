#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct node {
    int x;
    int y;
};

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<node> q;

        int fresh = 0;
        int day = 0;

        int m = grid.size(), n = grid[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    fresh++;
                } else if (grid[i][j] == 2) {
                    q.push({i, j});
                }
            }
        }

        while (!q.empty() && fresh > 0) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                node temp = q.front();
                q.pop();

                rot(grid, m, n, temp.x - 1, temp.y, q, fresh);
                rot(grid, m, n, temp.x + 1, temp.y, q, fresh);
                rot(grid, m, n, temp.x, temp.y - 1, q, fresh);
                rot(grid, m, n, temp.x, temp.y + 1, q, fresh);
            }
            day++;
        }

        return fresh > 0 ? -1 : day;
    }

    void rot(vector<vector<int>>& grid, int& m, int& n, int i, int j,
             queue<node>& q, int& fresh) {
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != 1)
            return;

        fresh--;
        grid[i][j] = 2;
        q.push({i, j});
    }
};

int main() {
    vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};

    Solution sol;

    cout << sol.orangesRotting(grid) << endl;
}

/*
2 1 1
1 1 0
0 1 1


*/
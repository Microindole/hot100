/*
// DFS
#include<bits/stdc++.h>

using namespace std;

bool inPos(int x, int n){
    if(x<n && x>=0){
        return true;
    }
    return false;
}

void getPos(int x,int y,vector<vector<int>>& res, int k, int n){
    res[x][y]++;
    if(k == 0){
        return;
    }
    if(inPos(x-1, n) && inPos(y+2, n)){
        res[x-1][y+2]++;
        getPos(x-1,y+2,res,k - 1,n);
    }
    if(inPos(x+1, n) && inPos(y+2, n)){
        res[x+1][y+2]++;
        getPos(x+1,y+2,res,k - 1,n);
    }
    if(inPos(x-1, n) && inPos(y-2, n)){
        res[x-1][y-2]++;
        getPos(x-1,y-2,res,k - 1,n);
    }
    if(inPos(x+1, n) && inPos(y-2, n)){
        res[x+1][y-2]++;
        getPos(x+1,y-2,res,k - 1,n);
    }

    if(inPos(x-2, n) && inPos(y+1, n)){
        res[x-2][y+1]++;
        getPos(x-2,y+1,res,k - 1,n);
    }
    if(inPos(x+2, n) && inPos(y+1, n)){
        res[x+2][y+1]++;
        getPos(x+2,y+1,res,k - 1,n);
    }
    if(inPos(x-2, n) && inPos(y-1, n)){
        res[x-2][y-1]++;
        getPos(x-2,y-1,res,k - 1,n);
    }
    if(inPos(x+2, n) && inPos(y-1, n)){
        res[x+2][y-1]++;
        getPos(x+2,y-1,res,k - 1,n);
    }
}

int main(){
    int n,k,x,y;
    cin>> n>>k;
    cin>>x>>y;
    x -=1;y-=1;
    vector<vector<int>> res(n,vector<int>(n,0));
    getPos(x,y,res,k,n);
    int times = 0;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(res[i][j]>0){
                times++;
            }
        }
    }
    cout<<times<<endl;
}
*/

// BFS
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 1. 定义一个结构体，清晰地打包三个变量
// 以后再也不用去记 pair 里面套 pair 那种反人类的写法了！
struct Node {
    int x;     // 当前所在行
    int y;     // 当前所在列
    int step;  // 走到这里花了多少步
};

// 2. 方向数组：马走日的 8 个固定跳法
// dx 代表行的变化，dy 代表列的变化，上下是对齐的
int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

int main() {
    int n, k;
    int start_x, start_y;
    cin >> n >> k;
    cin >> start_x >> start_y;

    start_x = start_x - 1;
    start_y = start_y - 1;
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    queue<Node> q;

    q.push({start_x, start_y, 0});
    visited[start_x][start_y] = true;

    int times = 1;

    while (!q.empty()) {
        Node curr = q.front();
        q.pop();

        if (curr.step == k) {
            continue;
        }
        for (int i = 0; i < 8; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && visited[nx][ny] == false) {
                visited[nx][ny] = true;
                times++;
                q.push({nx, ny, curr.step + 1});
            }
        }
    }
    cout << times << endl;

    return 0;
}

/*
4 1
1 1

4 2
1 1
*/
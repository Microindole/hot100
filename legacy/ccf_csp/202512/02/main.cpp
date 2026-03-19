#include <bits/stdc++.h>

using namespace std;

int f(int x, int k);

int g(int x, int k);

int g2x(int g, int k);

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> kList(m, 0);
    vector<int> aList(n, 0);
    vector<int> res(n, 0);
    for (int i = 0; i < m; i++) {
        cin >> kList[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> aList[i];
    }

    // ---------------------
    for (int i = 0; i < aList.size(); i++) {
        int temp = aList[i];
        for (int j = kList.size() - 1; j >= 0; j--) {
            temp = g2x(temp, kList[j]);
        }
        res[i] = temp;
    }
    // ---------------------
    // --- 满分优化开始 ---
    // 建立一个查表字典，记录最终结果 0~511 对应的初始数字是多少
    /*
    vector<int> lookup(512);

    // 只需要循环 512 次，每次跑 m 次逆运算
    for(int val = 0; val < 512; val++){
        int temp = val;
        for(int j = kList.size() - 1; j >= 0; j--){
            temp = g2x(temp, kList[j]);
        }
        lookup[val] = temp; // 记录下 1000 步逆运算后的祖宗是谁
    }

    // 针对题目给的 50 万个输入，直接 0 秒查表！
    for(int i = 0; i < aList.size(); i++){
        // aList[i] 是终态，lookup[aList[i]] 直接查出初态
        cout << lookup[aList[i]] << " ";
    }
    */
    //-------------------------

    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
    return 0;
}

int f(int x, int k) { return ((x * x + k * k) % 8) ^ k; }

int g(int x, int k) {
    int xa = x / 64;
    int xb = x / 8 % 8;
    int xc = x % 8;
    int ga = xb * 64;
    int gb = (xc ^ f(xb, k)) * 8;
    int gc = xa ^ f(xc, k);
    return ga + gb + gc;
}

int g2x(int g, int k) {
    int ga = g / 64, gb = g / 8 % 8, gc = g % 8;
    int xa = -1, xb = ga, xc = -1;
    xc = gb ^ f(xb, k);
    xa = gc ^ f(xc, k);
    return xa * 64 + xb * 8 + xc;
}
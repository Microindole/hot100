#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    // 前缀积 sumK, 前缀和 sumT
    // 下标从 1 开始方便处理区间 [i, j]
    vector<double> sumK(n + 1, 1.0);
    vector<double> sumT(n + 1, 0.0);

    for (int i = 1; i <= n; i++) {
        int type;
        double val;
        cin >> type >> val;

        // 继承前一个状态
        sumK[i] = sumK[i - 1];
        sumT[i] = sumT[i - 1];

        if (type == 1)
            sumK[i] *= val;  // 拉伸累乘
        else
            sumT[i] += val;  // 旋转累加
    }

    for (int k_idx = 0; k_idx < m; k_idx++) {
        int i, j;
        double x, y;
        cin >> i >> j >> x >> y;

        // O(1) 获取区间 [i, j] 的总变换
        double K = sumK[j] / sumK[i - 1];
        double T = sumT[j] - sumT[i - 1];

        // 先缩放
        x *= K;
        y *= K;

        // 再旋转（注意不要直接覆盖原变量）
        double newX = x * cos(T) - y * sin(T);
        double newY = x * sin(T) + y * cos(T);

        // 输出，保留适当小数即可，评测机会按误差范围判断
        cout << fixed << setprecision(3) << newX << " " << newY << "\n";
    }

    return 0;
}
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    double i;
    cin >> n >> i;

    vector<double> price(n + 1, 0.0);
    for (int j = 0; j <= n; j++) {
        cin >> price[j];
    }

    for (int j = n; j > 0; j--) {
        price[j - 1] += price[j] / (1 + i);
    }

    cout << fixed << setprecision(3) << price[0];
    return 0;
}

/*
2 0.05
-200 100 100
*/
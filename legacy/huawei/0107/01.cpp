#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string line;
    getline(cin, line);

    stringstream ss(line);

    vector<long> a;
    long ai;
    while (ss >> ai) {
        a.push_back(ai);
    }

    int n = a.size();
    vector<long> dp(n + 1, 0);
    if (n > 0) {
        dp[1] = max(dp[0], a[0]);
    }

    for (int i = 2; i <= n; i++) {
        dp[i] = max(dp[i - 1], dp[i - 2] + a[i - 1]);
    }

    cout << dp[n];

    return 0;
}
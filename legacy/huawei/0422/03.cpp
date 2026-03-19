#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    long long E;
    cin >> E;

    string line;
    getline(cin, line);

    vector<long long> a;
    long long temp;

    stringstream ssa(line);
    while (ssa >> temp) {
        a.push_back(temp);
    }

    vector<long long> b;
    getline(cin, line);

    stringstream ssb(line);
    while (ssb >> temp) {
        b.push_back(temp);
    }

    int n = a.size();

    vector<long long> dp(n + 1, -1);
    dp[0] = E;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j >= 1; j--) {
            if (dp[j - 1] > a[i]) {
                dp[j] = max(dp[j], dp[j - 1] - a[i] + b[i]);
            }
        }
    }

    for (int i = n; i >= 0; i++) {
        if (dp[i] != -1) {
            cout << dp[i] << endl;
            break;
        }
    }

    return 0;
}
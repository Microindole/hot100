#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> length(m + 1, 0);

    int start = 1;
    for (int i = 0; i < m; i++) {
        int lice;
        cin >> lice;

        int temp = lice - start - 1;
        start = lice;
        length[i] = temp > 0 ? temp : 0;
    }
    length[m] = n - start;

    vector<int> hold;
    for (int i = 0; i <= m; i++) {
        if (length[i] >= 3) {
            hold.push_back(length[i]);
        }
    }

    int size = hold.size();

    long long times = 0;
    long long max = 998244353;

    for (int i = 0; i < size; i++) {
        long long temp1 = hold[i] - 2;

        for (int j = 0; j < size; j++) {
            if (i == j && hold[i] >= 9) {
                long long temp = hold[i] - 7;
                times += (temp * (temp - 1) / 2 % max);
            } else {
                long long temp2 = hold[j] - 5;
                times += (temp1 * temp2 % max);
            }
        }
    }

    for (int i = 0; i < n - m - 9; i++) {
        times = (times * 26) % max;
    }

    cout << times;

    return 0;
}
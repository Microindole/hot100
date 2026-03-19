#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    long long l, r;
    cin >> l >> r;

    vector<long long> psum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        psum[i] = psum[i - 1] + p[i];
    }

    long long count = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            long long temp = psum[j] - psum[i];
            if (temp <= r && temp >= l) {
                count++;
            }
        }
    }

    cout << count;

    return 0;
}
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> dist(n), speed(n);
    for (int i = 0; i < n; i++) {
        cin >> dist[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> speed[i];
    }

    vector<double> retime(n);
    for (int i = 0; i < n; i++) {
        retime[i] = dist[i] * 1.0 / speed[i];
    }

    sort(retime.begin(), retime.end());

    int count = 0;

    for (int i = 0; i < n; i++) {
        if (retime[i] > 1.0 * i) {
            count++;
        } else {
            break;
        }
    }

    cout << count;

    return 0;
}
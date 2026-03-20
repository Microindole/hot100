// #include <iostream>
// #include <vector>

// using namespace std;

// int main() {
//     int n;
//     cin >> n;

//     vector<int> a(n + 1, 0), b(n + 1, 0), w(n + 1, 0), noproblem(n + 1, 0);
//     for (int i = 0; i < n + 1; i++) cin >> a[i];
//     for (int i = 1; i < n + 1; i++) cin >> b[i];

//     for (int j = 1; j <= n; j++) {
//         int temp = b[j];
//         b[j] = 0;
//         for (int i = n; i >= 0; i--) {
//             if (i == n) {
//                 noproblem[i] = a[i];
//             } else {
//                 if (noproblem[i + 1] - b[i + 1] <= 0) {
//                     noproblem[i] = a[i];
//                 } else {
//                     noproblem[i] = a[i] + noproblem[i + 1] - b[i + 1];
//                 }
//             }
//         }

//         w[j] = noproblem[0];
//         b[j] = temp;
//     }

//     for (int i = 1; i < n + 1; i++) {
//         cout << w[i] << " ";
//     }
//     return 0;
// }

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> a(n + 1, 0), b(n + 1, 0);
    for (int i = 0; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    vector<ll> S(n + 2, 0);
    S[n] = a[n];
    for (int i = n - 1; i >= 0; i--) {
        S[i] = max(a[i], a[i] + S[i + 1] - b[i + 1]);
    }

    vector<ll> E(n + 1, 0), excess(n + 1, 0);
    E[0] = S[0];
    excess[0] = 0;
    for (int i = 1; i <= n; i++) {
        E[i] = E[i - 1] - a[i - 1] + b[i];
        excess[i] = E[i] - S[i];
    }

    vector<ll> min_excess(n + 1, 0);
    min_excess[n] = excess[n];
    for (int i = n - 1; i > 0; i--) {
        min_excess[i] = min(excess[i], min_excess[i + 1]);
    }

    for (int i = 1; i <= n; i++) {
        ll count = b[i] - min_excess[i];
        ll res = S[0] + max(0ll, count);
        cout << res << " ";
    }

    return 0;
}

/*
3
5 5 5 5
0 100 0

3
9 4 6 2
9 4 6
*/
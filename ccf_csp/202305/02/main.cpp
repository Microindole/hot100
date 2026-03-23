#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, d;
    cin >> n >> d;

    vector<ll> W(n, 0);
    vector<vector<ll>> Q(n, vector<ll>(d, 0));
    vector<vector<ll>> K(n, vector<ll>(d, 0));
    vector<vector<ll>> V(n, vector<ll>(d, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            cin >> Q[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            cin >> K[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            cin >> V[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> W[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            Q[i][j] *= W[i];
        }
    }

    vector<vector<ll>> KtV(d, vector<ll>(d, 0));

    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            for (int k = 0; k < n; k++) {
                KtV[i][j] += K[k][i] * V[k][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            ll sum = 0;
            for (int k = 0; k < d; k++) {
                sum += Q[i][k] * KtV[k][j];
            }
            cout << sum << (j == d - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}

/*
3 2
1 2
3 4
5 6
10 10
-20 -20
30 30
6 5
4 3
2 1
4 0 -5
*/
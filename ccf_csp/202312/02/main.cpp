#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

ll getRes(ll temp, int k) {
    vector<vector<ll>> res;
    int cursor = -1;

    for (ll i = 2; i * i <= temp; i++) {
        if (temp % i != 0) {
            continue;
        }

        cursor++;
        res.push_back({i, 0});

        while (temp % i == 0) {
            temp /= i;
            res[cursor][1]++;
        }
    }
    if (temp != 1) {
        res.push_back({temp, 1});
    }

    ll returnRes = 1;
    for (int i = 0; i < res.size(); i++) {
        if (res[i][1] >= k) {
            for (int j = 0; j < res[i][1]; j++) {
                returnRes *= res[i][0];
            }
        }
    }
    return returnRes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin >> q;

    vector<ll> res(q, 1);

    for (int i = 0; i < q; i++) {
        ll num;
        int k;
        cin >> num >> k;
        res[i] = getRes(num, k);
    }

    for (int i = 0; i < q; i++) {
        cout << res[i] << "\n";
    }

    return 0;
}

/*
3
2155895064 3
2 2
10000000000 10
*/
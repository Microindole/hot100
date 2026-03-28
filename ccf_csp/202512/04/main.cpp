#include <iostream>
#include <unordered_set>

using namespace std;

long getD(long op, long n) {
    long a = 1, b = n, c, d = 0, e, g;
    if (op == 0) {
        for (; a <= n * n; a++) {
            c = n * n / a;
            if (n * n % a != 0) {
                continue;
            }
            e = 1;
            for (; e <= n * n; e++) {
                if ((n * n % e != 0) || (a * b % e != 0)) {
                    continue;
                }
                d += a * b / e;
            }
        }
    } else {
        for (; a <= n * n; a++) {
            c = n * n / a;
            if (n * n % a != 0) {
                continue;
            }
            e = 1;
            for (; e <= n * n; e++) {
                if ((n * n % e != 0) || (a * b % e != 0)) {
                    continue;
                }
                unordered_set<long> setd;
                setd.insert(a);
                setd.insert(n);
                setd.insert(c);
                setd.insert(a * b / e);
                setd.insert(e);
                setd.insert(n * n / e);
                if (setd.size() == 6) {
                    d += a * b / e;
                }
            }
        }
    }

    return d;
}

int main() {
    long op, n;
    cin >> op >> n;

    long res = 0;
    for (int i = 1; i <= n; i++) {
        res = (res + getD(op, i)) % 998244353;
    }

    cout << res % 998244353;
    return 0;
}
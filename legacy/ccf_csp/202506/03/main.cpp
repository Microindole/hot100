#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    if (n > 100) {
        return 0;
    }

    while (n--) {
        string m;
        cin >> m;
        if (m[0] == '0') {
            return 0;
        }
        long long decimal = 0;
        long long base = 1;

        for (int i = 58; i >= 1; i--) {
            if (m[i] == '1') {
                decimal += base;
            }

            base *= 2;
        }

        char a[40] = " 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
        char b[12];

        int n;
        int cnt;

        while (decimal != 0) {
            if ((decimal % 38) != 0) {
                b[++cnt] = a[decimal % 38];
            }
            decimal /= 38;
        }

        if (m[71] == '1') {
            for (int i = cnt; i > 0; i--) {
                cout << b[i];
            }

            cout << " ###" << "\n";
        }

        else {
            cout << "### ";
            for (int i = cnt; i > 0; i--) {
                cout << b[i];
            }
            cout << "\n";
        }
    }

    return 0;
}
#include <iostream>
#include <string>

using namespace std;

struct ky {
    string key;
    string value;
};

int main() {
    int s, d;
    cin >> s >> d;
    int i = 1;
    ky st[100];
    while (s--) {
        cin >> st[i].key >> st[i].value;
        i++;
    }

    string h;
    cin >> h;
    int n;
    cin >> n;
    while (n--) {
        int op;
        cin >> op;
        if (op == 1) {
            cin >> i;
            cout << st[i].key << ": " << st[i].value << "\n";
        }
        if (op == 2) {
            return 0;
        }
        if (op == 3) {
            int flag;
            cin >> flag;
            if (flag == 0) {
                string k, v;
                cin >> k >> v;
                if (k[0] == 'H' && k[1] == 'H') {
                    k = k.substr(1);
                }
                if (v[0] == 'H' && v[1] == 'H') {
                    v = v.substr(1);
                }
                cout << k << ": " << v << "\n";
            }
            if (flag > 0) {
                string v;
                cin >> v;
                if (v[0] == 'H' && v[1] == 'H') {
                    v = v.substr(1);
                }
                cout << st[flag].key << ": " << v << "\n";
            }
        }
    }

    return 0;
}
#include <iostream>
#include <vector>

using namespace std;

void setFront(int index, vector<int>& a, vector<int>& fa) {
    int n = a.size();

    int temp = a[index];
    for (int i = index; i < n; i++) {
        if (temp <= fa[i]) {
            break;
        }

        fa[i] = temp;
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> a, b;

    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        a.push_back(ai);
    }

    for (int i = 0; i < n; i++) {
        int bi;
        cin >> bi;
        b.push_back(bi);
    }

    vector<int> fa(n, INT_MIN), fb(n, INT_MIN);
    int temp = fa[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > temp) {
            temp = a[i];
        }

        fa[i] = temp;
    }

    temp = fb[0];

    for (int i = 0; i < n; i++) {
        if (b[i] > temp) {
            temp = b[i];
        }

        fb[i] = temp;
    }

    temp = fa[0];
    char who = 'c';
    int res = 0;

    for (int i = 0; i < n; i++) {
        if (fa[i] == fb[i]) {
            res++;
            continue;
        }

        if (fa[i] > fb[i]) {
            if (who == 'a' && a[i] == temp) {
                int site = a[i];
                a[i] = b[i];
                b[i] = site;

                setFront(i, b, fb);
                res++;
            }

            temp = fa[i];
            who = 'a';

        } else {
            if (who == 'b' && b[i] == temp) {
                int site = a[i];
                a[i] = b[i];
                b[i] = site;

                setFront(i, a, fa);
                res++;
            }
            temp = fb[i];
            who = 'b';
        }
    }

    cout << res << endl;
    return 0;
}
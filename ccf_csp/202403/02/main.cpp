#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

void toLowCase(string& s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += 32;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    unordered_set<string> nset, mset;
    string sTemp;
    for (int i = 0; i < n; i++) {
        cin >> sTemp;
        toLowCase(sTemp);
        nset.insert(sTemp);
    }
    for (int i = 0; i < m; i++) {
        cin >> sTemp;
        toLowCase(sTemp);
        mset.insert(sTemp);
    }

    int same = 0;

    for (string x : mset) {
        if (nset.count(x)) {
            same++;
        }
    }
    cout << same << "\n" << (nset.size() + mset.size() - same);

    return 0;
}

/*
9 7
Par les soirs bleus dete jirai dans les sentiers
PICOTIE PAR LES BLES FOULER LHERBE MENUE

*/
#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    int n, x, k;
    cin >> n >> x >> k;

    vector<int> s(k);
    for (int i = 0; i < k; i++) {
        cin >> s[i];
    }

    int m;
    cin >> m;

    map<int, vector<int>> usemap;
    while (m--) {
        int i, j;
        cin >> i >> j;

        usemap[j].push_back(i);
    }

    for (int i = 0; i < k; i++) {
        unordered_set<int> show;
        for (int j = s[i]; j < s[i] + x; j++) {
            for (int num : usemap[j]) {
                show.insert(num);
            }
        }

        cout << show.size() << " ";
    }
}

/*
4 2 2
3 4
4
2 4
2 3
1 2
3 5
*/
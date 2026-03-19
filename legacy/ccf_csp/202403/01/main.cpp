#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> word(m + 1, vector<int>(2, 0));

    for (int i = 0; i < n; i++) {
        vector<bool> show(m + 1, false);

        int l;
        cin >> l;

        for (int j = 0; j < l; j++) {
            int word_index;
            cin >> word_index;

            if (!show[word_index]) {
                word[word_index][0]++;
                show[word_index] = true;
            }
            word[word_index][1]++;
        }
    }

    for (int i = 1; i <= m; i++) {
        cout << word[i][0] << " " << word[i][1] << "\n";
    }

    return 0;
}

/*
4 3
5 1 2 3 2 1
1 1
3 2 2 2
2 3 2
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<char> s, t;

    for (int i = 0; i < n; i++) {
        char ch;
        cin >> ch;
        if (ch >= 'a' && ch <= 'z') {
            s.push_back(ch);
        }
    }

    int size = s.size();

    sort(s.begin(), s.end());

    int ou = 0, ji = size / 2;
    int index = 1;

    for (int i = 0; i < size; i++) {
        if (index % 2 == 1) {
            t.push_back(s[ji]);
            ji++;
        } else {
            t.push_back(s[ou]);
            ou++;
        }

        index++;
    }

    for (int i = 0; i < size; i++) {
        cout << t[i];
    }

    return 0;
}
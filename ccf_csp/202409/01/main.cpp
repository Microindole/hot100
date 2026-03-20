#include <iostream>
#include <string>
#include <vector>

using namespace std;

int check(string pwd) {
    int cnt[128] = {0};
    bool haveTwo = false, threeType = false;
    bool haveDigit = false, haveAlpha = false, haveChar = false;

    for (char ch : pwd) {
        cnt[ch]++;
        if (cnt[ch] > 2) haveTwo = true;
        if (isdigit(ch)) haveDigit = true;
        if (isalpha(ch)) haveAlpha = true;
        if (ch == '*' || ch == '#') haveChar = true;
    }
    threeType = haveDigit && haveAlpha && haveChar;

    if (!haveTwo && threeType) return 2;
    if (haveTwo && threeType) return 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<string> pwd(n, "");
    for (int i = 0; i < n; i++) {
        cin >> pwd[i];
    }

    for (int i = 0; i < n; i++) {
        cout << check(pwd[i]) << endl;
    }

    return 0;
}

/*
4
csp#ccsp
csp#ccsp2024
Csp#ccsp2024
CSP#2024
*/
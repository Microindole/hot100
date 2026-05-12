#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int getLength(string& res, int left, int right) {
    while (left >= 0 && right < res.size() && res[left] == res[right]) {
        left--;
        right++;
    }

    return right - left - 1;
}

string getRes(string& s) {
    if (s.empty())
        return "";
    int start = 0, maxLen = 0;

    string result = "";

    for (int i = 0; i < s.length(); ++i) {
        int len1 = getLength(s, i, i);
        int len2 = getLength(s, i, i + 1);

        int curLen = max(len1, len2);
        if (curLen >= maxLen) {
            start = i - (curLen - 1) / 2;

            string temp = s.substr(start, maxLen);

            if (curLen > maxLen) {
                maxLen = curLen;
                int start = i - (curLen - 1) / 2;
                result = s.substr(start, maxLen);
            } else if (curLen == maxLen && maxLen > 0) {
                int start = i - (curLen - 1) / 2;
                string temp = s.substr(start, maxLen);
                if (temp < result) {
                    result = temp;
                }
            }
        }
    }

    return result;
}

int main() {
    int n;
    cin >> n;

    string res = "";

    if (n < 0) {
        res.push_back('b');
        n = 0 - n;
    } else {
        res.push_back('a');
    }

    cin.ignore();

    string line;
    getline(cin, line);
    vector<int> b;

    int b_val;

    stringstream ss(line);
    while (ss >> b_val) {
        b.push_back(b_val);
    }

    for (int i : b) {
        int d = n % i;
        n = n / i;

        res.push_back((char)(d + 'a'));
    }

    string result = getRes(res);
    cout << result;

    if (result == res) {
        cout << "(palindrome)";
    }

    return 0;
}
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool wordPattern(string pattern, string s) {
    vector<string> sList;

    int n = s.size();
    int start = n;
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] != ' ') {
            if (i < start) {
                start = i;
            }
            index++;
        }
        if (s[i] == ' ' || i == n - 1) {
            string temp = s.substr(start, index);
            start = n;
            if (index != 0) {
                sList.push_back(temp);
            }
            index = 0;
        }
    }

    if (pattern.size() != sList.size()) {
        return false;
    }

    unordered_map<char, string> ps;
    unordered_map<string, char> sp;
    for (int i = 0; i < pattern.size(); i++) {
        char ch = pattern[i];
        string word = sList[i];

        if (ps.count(ch) && ps[ch] != word) {
            return false;
        }

        if (sp.count(word) && sp[word] != ch) {
            return false;
        }

        ps[ch] = word;
        sp[word] = ch;
    }

    return true;
}

int main() {
    string pattern = "abba", s = "dog cat cat dog";
    cout << "----" << "\n";
    if (wordPattern(pattern, s)) {
        cout << "1";
    } else {
        cout << "0";
    }
    return 0;
}
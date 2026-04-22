#include <iostream>
#include <stack>
#include <string>

using namespace std;

string decodeString(string s) {
    stack<string> saveString;
    string curr = "";

    int n = s.size();

    for (int i = 0; i < n; i++) {
        if (s[i] <= '9' && s[i] >= '0') {
            int ssize = curr.size();
            if (ssize == 0 || curr[ssize - 1] <= '9' && curr[ssize - 1] >= '0') {
                curr += s[i];
            } else {
                saveString.push(curr);
                curr = s[i];
            }
        } else if (s[i] == '[') {
            saveString.push(curr);
            saveString.push("[");
            curr = "";
        } else if (s[i] == ']') {
            string top = saveString.top();
            saveString.pop();

            while (top != "[") {
                curr = top + curr;
                saveString.pop();
                top = saveString.top();
            }
            saveString.pop();

            top = saveString.top();
            saveString.pop();

            int times = stoi(top);

            string temp = curr;

            for (int j = 1; j < times; j++) {
                curr += temp;
            }

            if (times == 0) curr = "";

            saveString.push(curr);
            curr = "";

        }

        else {
            curr += s[i];
        }
    }

    while (!saveString.empty()) {
        string top = saveString.top();
        saveString.pop();
        curr = top + curr;
    }

    return curr;
}

int main() {
    string s;
    cin >> s;

    cout << decodeString(s);

    return 0;
}
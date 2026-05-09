#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        int charRows[26];
        string rows[] = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};

        for (int i = 0; i < 3; i++) {
            for (char c : rows[i]) {
                charRows[c - 'a'] = i;
            }
        }

        vector<string> res;
        for (const string& word : words) {
            if (word.empty()) {
                continue;
            }

            int rowIdx = charRows[tolower(word[0]) - 'a'];

            bool isValid = true;

            for (int i = 1; i < word.length(); i++) {
                if (charRows[tolower(word[i]) - 'a'] != rowIdx) {
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                res.push_back(word);
            }
        }

        return res;
    }
};

int main() {
    vector<string> words = {"Hello", "Alaska", "Dad", "Peace"};
    Solution so;

    vector<string> res = so.findWords(words);

    for (const string& i : res) {
        cout << i << " ";
    }
}
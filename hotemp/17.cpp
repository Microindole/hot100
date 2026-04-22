#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    void getRes(string digits, int size, int index, string& curr, const vector<string> phone, vector<string>& res) {
        if (index == size) {
            res.push_back(curr);
            return;
        }

        int digit = digits[index] - '0';
        string letters = phone[digit];
        for (int i = 0; i < letters.size(); i++) {
            curr.push_back(letters[i]);
            getRes(digits, size, index + 1, curr, phone, res);
            curr.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        vector<string> phone = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

        vector<string> res;

        string curr = "";

        int size = digits.size();
        int index = 0;

        getRes(digits, size, index, curr, phone, res);

        return res;
    }
};

int main() {
    string s;
    cin >> s;

    Solution so;

    vector<string> res = so.letterCombinations(s);

    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }

    return 0;
}
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    void getShort(const string& s, int& resl, int& len, int index) {
        int len1 = -1, len2 = 0;
        int l1 = index, r1 = index, l2 = index, r2 = index + 1;
        while (l1 >= 0 && r1 < s.size() && s[l1] == s[r1]) {
            l1--;
            r1++;
            len1 += 2;
        }

        while (l2 >= 0 && r2 < s.size() && s[l2] == s[r2]) {
            l2--;
            r2++;
            len2 += 2;
        }

        if (len1 > len) {
            len = len1;
            resl = l1 + 1;
        }
        if (len2 > len) {
            len = len2;
            resl = l2 + 1;
        }
    }

    string longestPalindrome(string s) {
        int resl = 0;
        int len = 1;

        for (int i = 0; i < s.size(); i++) {
            getShort(s, resl, len, i);
        }

        return s.substr(resl, len);
    }
};

int main() {
    string s2 = "bb";
    Solution sol;

    cout << "\n" << sol.longestPalindrome(s2) << endl;
}
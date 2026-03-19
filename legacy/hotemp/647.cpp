/**
 * 中心扩展法
 */

#include <string>

using namespace std;

class Solution {
public:
    int countSubstrings(string s) {
        int count = 0;
        int n = s.size();

        for (int i = 0; i < n; i++) {
            count += extend(s, i, i, n);
            count += extend(s, i, i + 1, n);
        }

        return count;
    }

    int extend(string& s, int i, int j, int n) {
        int res = 0;
        while (i >= 0 && j < n && s[i] == s[j]) {
            i--;
            j++;
            res++;
        }

        return res;
    }
};
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty())
            return 0;

        int n = haystack.size(), m = needle.size();

        vector<int> next(m, 0);
        int j = 0;
        for (int i = 1; i < m; i++) {
            while (j > 0 && needle[i] != needle[j]) {
                j = next[j - 1];
            }

            if (needle[i] == needle[j]) {
                j++;
            }

            next[i] = j;
        }

        j = 0;
        for (int i = 0; i < n; i++) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }

            if (haystack[i] == needle[j]) {
                j++;
            }

            if (j == m) {
                return i - m + 1;
            }
        }

        return -1;
    }
};
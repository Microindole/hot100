#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int n = word1.size(), m = word2.size();

        string res = "";
        if (n <= m) {
            for (int i = 0; i < n; i++) {
                res.push_back(word1[i]);
                res.push_back(word2[i]);
            }

            res += word2.substr(n, m - n);
        } else {
            for (int i = 0; i < m; i++) {
                res.push_back(word1[i]);
                res.push_back(word2[i]);
            }

            res += word1.substr(m, n - m);
        }

        return res;
    }
};
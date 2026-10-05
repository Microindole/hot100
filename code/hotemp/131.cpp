#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isCircle(string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right])
                return false;

            left++;
            right--;
        }

        return true;
    }

    void dfs(string& s, vector<vector<string>>& res, vector<string>& path,
             int start) {
        if (start == s.size()) {
            res.push_back(path);
        }

        for (int i = start; i < s.size(); i++) {
            if (isCircle(s, start, i)) {
                path.push_back(s.substr(start, i - start + 1));
                dfs(s, res, path, i + 1);

                path.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> path;

        dfs(s, res, path, 0);

        return res;
    }
};
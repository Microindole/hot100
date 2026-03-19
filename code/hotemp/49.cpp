#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> info;

        for (const string& str : strs) {
            string key = str;
            sort(key.begin(), key.end());

            info[key].push_back(str);
        }

        vector<vector<string>> res;
        for (const auto& i : info) {
            res.push_back(i.second);
        }

        return res;
    }
};
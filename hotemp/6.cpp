#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1 || s.size() <= numRows) return s;

        int n = s.size();

        vector<string> res(numRows);

        int thisRow = 0;
        bool goingDown = false;

        for (char c : s) {
            res[thisRow].push_back(c);

            if (thisRow == 0 || thisRow == numRows - 1) {
                goingDown = !goingDown;
            }

            thisRow += goingDown ? 1 : -1;
        }

        string ans = "";
        for (string& row : res) {
            ans += row;
        }

        return ans;
    }
};
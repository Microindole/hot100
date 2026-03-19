#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.size() < t.size())
            return "";

        string res = "";
        int len = s.size() + 1;

        unordered_map<char, int> target, now;

        int l = 0, r = 0, start = 0;

        for (char c : t) {
            target[c]++;
        }

        int valid = 0;

        while (r < s.size()) {
            if (target.count(s[r])) {
                now[s[r]]++;

                if (now[s[r]] == target[s[r]]) {
                    valid++;
                }
            }

            while (valid == target.size()) {
                int temp = r - l + 1;
                if (temp < len) {
                    len = temp;
                    start = l;
                }

                if (target.count(s[l])) {
                    if (now[s[l]] == target[s[l]]) {
                        valid--;
                    }

                    now[s[l]]--;
                }

                l++;
            }

            r++;
        }
        return len == s.size() + 1 ? "" : s.substr(start, len);
    }
};
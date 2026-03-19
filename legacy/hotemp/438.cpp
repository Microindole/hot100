#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int s_len = s.length(), p_len = p.length();
        if (s_len < p_len)
            return {};

        vector<int> res;
        vector<int> s_cnt(26, 0);
        vector<int> p_cnt(26, 0);

        for (int i = 0; i < p_len; i++) {
            p_cnt[p[i] - 'a']++;
            s_cnt[s[i] - 'a']++;
        }

        if (s_cnt == p_cnt) {
            res.push_back(0);
        }

        for (int i = 0; i < s_len - p_len; i++) {
            s_cnt[s[i] - 'a']--;
            s_cnt[s[i + p_len] - 'a']++;

            if (s_cnt == p_cnt) {
                res.push_back(i + 1);
            }
        }

        return res;
    }
};
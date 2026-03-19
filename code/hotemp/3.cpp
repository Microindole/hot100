#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> uset;

        int maxLen = 0;

        int start = 0;
        for (int i = 0; i < s.size(); i++) {
            if (uset.count(s[i])) {
                int len = i - start;
                maxLen = max(len, maxLen);

                while (uset.count(s[i])) {
                    uset.erase(s[start]);
                    start++;
                }
            }
            uset.insert(s[i]);
        }

        return max(maxLen, static_cast<int>(s.size()) - start);
    }
};
#include <algorithm>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> isSon;

        int n = s.size();

        int start = 0;
        int maxLength = 0;

        for (int i = 0; i < n; i++) {
            if (isSon.count(s[i])) {
                int length = i - start;
                maxLength = max(maxLength, length);

                while (isSon.count(s[i])) {
                    isSon.erase(s[start]);
                    start++;
                }
            }
            isSon.insert(s[i]);
        }

        return max(maxLength, n - start);
    }
};
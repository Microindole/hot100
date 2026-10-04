#include <climits>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int n = s.size();

        vector<int> last(26);

        for (int i = 0; i < n; i++) {
            last[s[i] - 'a'] = i;
        }

        vector<int> res;
        int start = 0;
        int maxReach = INT_MIN;

        for (int i = 0; i < n; i++) {
            maxReach = max(maxReach, last[s[i] - 'a']);

            if (i == maxReach) {
                res.push_back(i - start + 1);
                start = i + 1;
            }
        }

        return res;
    }
};
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> dic(nums.begin(), nums.end());

        int maxLen = 0;
        for (int x : dic) {
            if (!dic.count(x - 1)) {
                int temp = x;
                int templen = 0;
                while (dic.count(temp)) {
                    templen++;
                    temp++;
                }
                maxLen = max(templen, maxLen);
            }
        }

        return maxLen;
    }
};
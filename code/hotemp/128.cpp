#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> info(nums.begin(), nums.end());

        int maxLen = 0;
        for (int i : info) {
            if (!info.count(i - 1)) {
                int temp = i;
                int len = 0;

                while (info.count(temp)) {
                    len++;
                    temp++;
                }

                maxLen = max(len, maxLen);
            }
        }

        return maxLen;
    }
};

int main() {
    vector<int> nums = {1};

    Solution sol;

    cout << sol.longestConsecutive(nums) << endl;

    return 0;
}
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> count_map;
        for (int x : nums) {
            count_map[x]++;
        }

        int res = 0;
        for (const auto& [key, value] : count_map) {
            if (count_map.count(key + 1)) {
                res = max(res, count_map[key] + count_map[key + 1]);
            }
        }

        return res;
    }
};
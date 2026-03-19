#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> umap;

        umap[0] = 1;

        int sum = 0, res = 0;

        for (int num : nums) {
            sum += num;

            int target = sum - k;

            if (umap.count(target)) {
                res += umap[target];
            }

            umap[sum]++;
        }
        return res;
    }
};
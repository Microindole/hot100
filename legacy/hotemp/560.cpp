#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> frontSum(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            frontSum[i] = frontSum[i - 1] + nums[i - 1];
        }

        unordered_map<int, int> show;
        show[0]++;

        int res = 0;

        for (int i = 1; i <= n; i++) {
            int need = frontSum[i] - k;
            if (show.count(need)) {
                res += show[need];
            }

            show[frontSum[i]]++;
        }

        return res;
    }
};
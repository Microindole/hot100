#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> show;

        for (int i = 0; i < n - 2; i++) {
            if (nums[i] > 0) break;

            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int j = i + 1;
            int k = n - 1;

            while (j < k) {
                int temp = nums[i] + nums[j] + nums[k];
                if (temp == 0) {
                    show.push_back({nums[i], nums[j], nums[k]});

                    while (j < k && nums[j] == nums[j + 1]) j++;
                    while (j < k && nums[k] == nums[k - 1]) k--;

                    j++;
                    k--;
                } else if (temp < 0) {
                    j++;
                } else {
                    k--;
                }
            }
        }

        return show;
    }
};
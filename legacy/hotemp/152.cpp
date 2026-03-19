#include <vector>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.empty())
            return 0;

        int max_so_far = nums[0];
        int min_so_far = nums[0];
        int result = max_so_far;

        for (size_t i = 1; i < nums.size(); i++) {
            int curr = nums[i];

            if (curr < 0) {
                swap(max_so_far, min_so_far);
            }

            max_so_far = max(curr, max_so_far * curr);
            min_so_far = min(curr, min_so_far * curr);

            result = max(result, max_so_far);
        }

        return result;
    }
};
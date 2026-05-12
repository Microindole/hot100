#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty())
            return 0;

        // tails[i] 存储长度为 i + 1 的子序列的最小末尾
        vector<int> tails;

        for (int x : nums) {
            // 在 tails 中二分查找第一个大于等于 x 的位置
            auto it = lower_bound(tails.begin(), tails.end(), x);

            if (it == tails.end()) {
                // 如果 x 比所有末尾都大，直接添加
                tails.push_back(x);
            } else {
                // 否则，用更小的 x 更新当前的末尾
                *it = x;
            }
        }

        // tails 的长度就是最长递增子序列的长度
        return tails.size();
    }
};
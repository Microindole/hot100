#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution1 {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> show;

        for (int i = 0; i < nums.size(); i++) {
            if (show.count(nums[i]) && i - show[nums[i]] <= k) {
                return true;
            }
            show[nums[i]] = i;
        }

        return false;
    }
};

class Solution2 {
public:
    /**
     * @brief 判断数组中是否存在满足索引差值不超过 k 的重复元素（滑动窗口法）。
     *
     * @details
     * ### 滑动窗口模拟图 (以 nums = [1,2,3,1,2], k = 2 为例)
     * @code
     * i = 0: nums[0]=1, 窗口 [1]       (大小 1 <= 2)
     * i = 1: nums[1]=2, 窗口 [1, 2]    (大小 2 <= 2)
     *
     * i = 2: 窗口大小即将超标！
     *        先从集合中移除最左侧元素 nums[2-2-1] = nums[-1] (此处不触发)
     *        nums[2]=3, 窗口变为 [2, 3] (移除 1 后加入 3)
     *
     * i = 3: 准备加入 nums[3]=1
     *        先移除超期元素 nums[3-2-1] = nums[0] = 1 (集合中本来就没有 1)
     *        此时集合为 [2, 3]，无重复，加入 1 ──► 窗口变为 [2, 3, 1]
     *
     * i = 4: 准备加入 nums[4]=2
     *        先移除超期元素 nums[4-2-1] = nums[1] = 2 ──► 集合变为 [3, 1]
     *        检查 nums[4]=2 是否在集合中 ──► 不在，加入 2 ──► 窗口 [3, 1, 2]
     * @endcode
     *
     * ### 复杂度分析
     * - **时间复杂度**: O(N)。虽然有擦除操作，但每个元素最多被加入集合
     *   一次，被移出集合一次，哈希集合的增删查平均都是 O(1)。
     * - **空间复杂度**: O(min(N, k))。哈希集合的大小被严格限制在 k 以内。
     *   当 k 远小于 N 时，该方案比记录索引法更省内存。
     *
     * @param nums 输入的整数数组引用。
     * @param k 允许的最大索引差值（窗口最大长度为 k）。
     * @return true 如果在大小为 k 的窗口内发现重复元素。
     * @return false 如果遍历完数组均未发现。
     */
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> window;

        for (int i = 0; i < nums.size(); i++) {
            if (i > k) {
                window.erase(nums[i - k - 1]);
            }

            if (window.count(nums[i])) {
                return true;
            }

            window.insert(nums[i]);
        }

        return false;
    }
};

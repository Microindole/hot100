#include <deque>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        deque<int> dq;  // 存储下标，保持对应的数值单调递减

        for (int i = 0; i < nums.size(); ++i) {
            // 1. 保持单调性：如果当前值大于等于队尾值，队尾就没用了
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }

            // 2. 将当前下标入队
            dq.push_back(i);

            // 3. 检查队头是否过期：如果队头下标已在窗口左侧之外
            if (dq.front() == i - k) {
                dq.pop_front();
            }

            // 4. 窗口已形成（长度达到 k），开始记录答案
            if (i >= k - 1) {
                res.push_back(nums[dq.front()]);
            }
        }
        return res;
    }
};
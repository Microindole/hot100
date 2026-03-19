#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        int now = n + 1;

        for (int i = 0; i < n; i++) {
            if (nums[i] == i + 1) {
                continue;
            }

            else {
                now = nums[i];
                while (now > 0 && now <= n && now != nums[now - 1]) {
                    int temp = nums[now - 1];
                    nums[now - 1] = now;
                    now = temp;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1)
                return i + 1;
        }

        return n + 1;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {2, 1};

    cout << sol.firstMissingPositive(nums) << endl;
}
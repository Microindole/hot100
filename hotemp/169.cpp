#include <vector>

using namespace std;

int majorityElement(vector<int>& nums) {
    int res = nums[0];
    int count = 0;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        if (nums[i] == res) {
            count++;
        } else {
            if (count == 0) {
                count = 1;
                res = nums[i];
            } else {
                count--;
            }
        }
    }

    return res;
}
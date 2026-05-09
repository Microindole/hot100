#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();

        int index = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == val) {
                n--;
            } else {
                nums[index] = nums[i];
                index++;
            }
        }

        return n;
    }
};

int main() {
    vector<int> nums = {0, 1, 2, 2, 3, 0, 4, 2};

    int val = 2;

    Solution sol;
    int n = sol.removeElement(nums, val);

    cout << n << endl;

    for (int i = 0; i < n; i++) {
        cout << nums[i] << " ";
    }
}
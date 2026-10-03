#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int res = nums[0];

        for (int i : nums) {
            if (i == res) {
                count++;
            } else {
                count--;
                if (count == 0) {
                    count = 1;
                    res = i;
                }
            }
        }

        return res;
    }
};
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        unordered_map<int, int> show;

        int n = 0;

        int index = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (show[nums[i]] == 2) {
                n++;
            } else {
                nums[index] = nums[i];
                index++;
                show[nums[i]]++;
            }
        }

        while (n--) {
            nums.pop_back();
        }

        return nums.size();
    }
};
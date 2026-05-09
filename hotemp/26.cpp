#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        unordered_set<int> show;

        int n = nums.size();

        int index = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (show.count(nums[i])) {
                n--;
            } else {
                nums[index] = nums[i];
                index++;
                show.insert(nums[i]);
            }
        }

        return n;
    }
};
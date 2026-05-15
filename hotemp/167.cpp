#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n = numbers.size();

        int left = 0, right = n - 1;

        while (numbers[left] + numbers[right] != target) {
            int temp = numbers[left] + numbers[right];

            if (temp > target) {
                right--;
            } else if (temp < target) {
                left++;
            }
        }

        return {left + 1, right + 1};
    }
};
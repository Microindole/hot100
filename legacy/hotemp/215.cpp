#include <random>
#include <vector>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int target = nums.size() -
                     k;  // 第 k 大即为升序排序后的第 n-k 个（索引从 0 开始）
        int left = 0, right = nums.size() - 1;

        while (true) {
            int pivotIndex = partition(nums, left, right);
            if (pivotIndex == target) {
                return nums[pivotIndex];
            } else if (pivotIndex < target) {
                left = pivotIndex + 1;
            } else {
                right = pivotIndex - 1;
            }
        }
    }

private:
    int partition(vector<int>& nums, int left, int right) {
        // 随机选择 pivot 避免极端退化情况
        int randomIndex = left + rand() % (right - left + 1);
        swap(nums[randomIndex], nums[right]);

        int pivot = nums[right];
        int i = left;
        for (int j = left; j < right; j++) {
            if (nums[j] <= pivot) {
                swap(nums[i++], nums[j]);
            }
        }
        swap(nums[i], nums[right]);
        return i;
    }
};
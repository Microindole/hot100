#include <algorithm>
#include <climits>
#include <vector>

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        // 确保 nums1 是较短的数组，减少二分次数，并防止 j 出现负数
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = nums1.size();
        int n = nums2.size();
        int left = 0, right = m;

        // 总长度的一半（进位处理奇偶）
        int halfLen = (m + n + 1) / 2;

        while (left <= right) {
            int i = left + (right - left) / 2;  // nums1 的划分点
            int j = halfLen - i;                // nums2 的划分点

            // i 需要增大：nums1[i] 太小了
            if (i < right && nums2[j - 1] > nums1[i]) {
                left = i + 1;
            }
            // i 需要减小：nums1[i-1] 太大了
            else if (i > left && nums1[i - 1] > nums2[j]) {
                right = i - 1;
            }
            // 找到完美的划分点
            else {
                int maxLeft = 0;
                if (i == 0)
                    maxLeft = nums2[j - 1];
                else if (j == 0)
                    maxLeft = nums1[i - 1];
                else
                    maxLeft = std::max(nums1[i - 1], nums2[j - 1]);

                // 如果总长度是奇数，直接返回左半部分最大值
                if ((m + n) % 2 == 1) return maxLeft;

                int minRight = 0;
                if (i == m)
                    minRight = nums2[j];
                else if (j == n)
                    minRight = nums1[i];
                else
                    minRight = std::min(nums1[i], nums2[j]);

                // 如果总长度是偶数，返回左右边界的平均值
                return (maxLeft + minRight) / 2.0;
            }
        }
        return 0.0;
    }
};
#include <iostream>
#include <vector>

using namespace std;

/*
LeetCode 33 - Search in Rotated Sorted Array

思路：
1. 先用二分找到旋转数组的“转折点” k
   满足：
       nums[k] > nums[k + 1]

2. 转折点把数组分成两个有序区间：

       [ left half ]        [ right half ]
     4   5   6   7   |   0   1   2
                 ^       ^
                 k      k+1

   其中：
       [0, k]     严格递增
       [k+1, n-1] 严格递增

3. 分别在两个有序区间里做普通二分查找。


--------------------------------------------------
一、如何找转折点 k
--------------------------------------------------

例子：

nums = [4, 5, 6, 7, 0, 1, 2]

下标：
        0  1  2  3  4  5  6
        4  5  6  7  0  1  2
L = 0            M = 3         R = 6

mid = 3

检查：

    nums[mid + 1] < nums[mid]

    nums[4] < nums[3]
       0    <    7

成立，所以：

    k = 3

转折点就是：

        4  5  6  7 | 0  1  2
                 ^
                 k


--------------------------------------------------
二、如果 mid 不是转折点
--------------------------------------------------

情况 1：

    nums[mid] < nums[left]

说明 mid 已经落在旋转后的“小值区域”。

例如：

        6  7  0  1  2  4  5
        ^        ^
      left      mid

这里：

    nums[mid] = 1
    nums[left] = 6

    1 < 6

说明转折点一定在：

    [left, mid]

所以：

    right = mid

注意不能直接：

    right = mid - 1

因为 mid 仍然可能是转折边界的一部分。


情况 2：

    nums[mid] >= nums[left]

并且 mid 本身不是转折点。

例如：

        4  5  6  7  0  1  2
        ^     ^
      left   mid

这里：

    nums[mid] = 6
    nums[left] = 4

    6 >= 4

说明当前还处于左边的“大值递增区域”，
转折点一定在右边：

    [mid, right]

所以：

    left = mid


--------------------------------------------------
三、为什么 left = mid 不会死循环
--------------------------------------------------

一般二分里：

    left = mid

确实有死循环风险。

例如：

    left = 3
    right = 4

则：

    mid = 3

如果再次：

    left = mid

区间就不会缩小。

但是这里我们在更新 left 之前先检查：

    if (nums[mid + 1] < nums[mid])
        return mid;

当区间只剩两个元素：

    left = 3
    right = 4
    mid = 3

如果这里存在旋转断点，那么一定有：

    nums[4] < nums[3]

于是会直接 return 3，
不会执行 left = mid。

所以在本题“元素互不相同”的前提下，
这套写法不会卡死。


--------------------------------------------------
四、特殊情况：没有旋转
--------------------------------------------------

例如：

    1  2  3  4  5
    ^           ^
   left        right

因为：

    nums[left] < nums[right]

说明整个数组已经严格递增，没有发生旋转。

直接返回：

    k = -1

然后对整个数组做一次普通二分即可。


--------------------------------------------------
五、找到转折点后的搜索
--------------------------------------------------

例如：

    nums = [4, 5, 6, 7, 0, 1, 2]

找到：

    k = 3

数组被分成：

    [4, 5, 6, 7]    [0, 1, 2]
     0         3      4      6

两个区间内部都是严格递增的。

因此：

    binary search [0, k]

如果没找到，再：

    binary search [k + 1, n - 1]


总时间复杂度：

    找转折点：O(log n)
    左半边二分：O(log n)
    右半边二分：O(log n)

总复杂度：

    O(log n)
*/
class Solution {
public:
    int getK(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;

        if (nums.size() <= 1 || nums[left] < nums[right]) {
            return -1;
        }

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid + 1] < nums[mid]) {
                return mid;
            }

            if (nums[mid] < nums[left]) {
                right = mid;
            } else {
                left = mid;
            }
        }

        return -1;
    }

    int search2(vector<int>& nums, int target, int left, int right) {
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }

    int search(vector<int>& nums, int target) {
        int dis = getK(nums);
        int left = 0, right = nums.size() - 1;

        if (dis == -1) {
            return search2(nums, target, left, right);
        }

        int res = search2(nums, target, left, dis);

        return res == -1 ? search2(nums, target, dis + 1, right) : res;
    }
};
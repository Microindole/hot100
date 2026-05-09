#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int indexm = m - 1, indexn = n - 1, index = m + n - 1;

        while (indexm >= 0 && indexn >= 0) {
            if (nums1[indexm] >= nums2[indexn]) {
                nums1[index] = nums1[indexm];
                indexm--;
            } else {
                nums1[index] = nums2[indexn];
                indexn--;
            }
            index--;
        }

        while (indexn >= 0) {
            nums1[index] = nums2[indexn];
            indexn--;
            index--;
        }
    }
};
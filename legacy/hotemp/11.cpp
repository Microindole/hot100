#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int maxArea = 0;

        while (r > l) {
            int hl = height[l], hr = height[r];

            if (hl <= hr) {
                maxArea = max(maxArea, (r - l) * hl);
                l++;
            } else {
                maxArea = max(maxArea, (r - l) * hr);
                r--;
            }
        }

        return maxArea;
    }
};
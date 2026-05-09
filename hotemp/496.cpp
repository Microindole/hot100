#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> show;

        for (int i = 0; i < nums2.size(); i++) {
            show[nums2[i]] = i;
        }

        stack<int> s;

        vector<int> dan(nums2.size(), -1);

        for (int i : nums2) {
            while (!s.empty() && s.top() < i) {
                int temp = s.top();
                s.pop();
                dan[show[temp]] = i;
            }

            s.push(i);
        }

        vector<int> res(nums1.size(), -1);
        for (int i = 0; i < nums1.size(); i++) {
            int index = show[nums1[i]];
            res[i] = dan[index];
        }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> nums1 = {2, 4}, nums2 = {1, 2, 3, 4};
    Solution so;

    vector<int> res = so.nextGreaterElement(nums1, nums2);

    for (int i : res) {
        cout << i << " ";
    }

    return 0;
}
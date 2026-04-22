#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> topKFrequent(vector<int>& nums, int k) {
    vector<int> res;

    int n = nums.size();

    unordered_map<int, int> times;
    for (int i : nums) {
        times[i]++;
    }

    vector<vector<int>> bucket(n + 1);
    for (const auto& t : times) {
        bucket[t.second].push_back(t.first);
    }

    for (int i = bucket.size() - 1; i >= 0; i--) {
        for (int j : bucket[i]) {
            res.push_back(j);
            if (res.size() == k) {
                return res;
            }
        }
    }

    return res;
}

int main() {
    vector<int> nums = {1, 2, 1, 2, 1, 2, 3, 1, 3, 2};
    int k = 2;

    vector<int> res = topKFrequent(nums, k);

    cout << "[ ";
    for (int i : res) {
        cout << i << " ";
    }
    cout << "]";

    return 0;
}
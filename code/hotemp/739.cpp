#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> temp;

        int n = temperatures.size();

        vector<int> res(n, 0);
        for (int i = 0; i < n; i++) {
            while (!temp.empty() &&
                   temperatures[i] > temperatures[temp.top()]) {
                int day = temp.top();
                temp.pop();

                res[day] = i - day;
            }

            temp.push(i);
        }

        return res;
    }
};

int main() {
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};

    Solution sol;
    vector<int> res = sol.dailyTemperatures(temperatures);

    for (int i : res) {
        cout << i << " ";
    }
}
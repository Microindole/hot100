#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        int minPrice = prices[0];

        for (int i = 1; i < prices.size(); i++) {
            res = max(res, prices[i] - minPrice);

            minPrice = min(prices[i], minPrice);
        }

        return res;
    }
};
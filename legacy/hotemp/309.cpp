#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        if (n == 0) {
            return 0;
        }

        int f0 = -prices[0];
        int f1 = 0, f2 = 0;

        for (int i = 1; i < n; i++) {
            int new_f0 = max(f0, f2 - prices[i]);
            int new_f1 = f0 + prices[i];
            int new_f2 = max(f1, f2);

            f0 = new_f0;
            f1 = new_f1;
            f2 = new_f2;
        }

        return max(f1, f2);
    }
};
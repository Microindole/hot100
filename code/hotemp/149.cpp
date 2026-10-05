#include <algorithm>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 2)
            return n;
        int max_pts = 0;

        for (int i = 0; i < n; i++) {
            unordered_map<string, int> count;
            int local_max = 0;

            for (int j = i + 1; j < n; j++) {
                int dy = points[j][1] - points[i][1];
                int dx = points[j][0] - points[i][0];

                // 如果 dx == 0 (垂直线)，强行让 dy > 0
                if (dx < 0 || (dx == 0 && dy < 0)) {
                    dx = -dx;
                    dy = -dy;
                }

                int g = gcd(dy, dx);
                string key = to_string(dy / g) + "_" + to_string(dx / g);

                count[key]++;
                local_max = max(local_max, count[key]);
            }
            max_pts = max(max_pts, local_max + 1);
        }
        return max_pts;
    }
};
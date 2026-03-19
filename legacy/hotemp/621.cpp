#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int size = tasks.size();

        int times[26] = {0};

        for (char ch : tasks) {
            times[ch - 'A']++;
        }

        int max = 0;
        for (int i : times) {
            if (i > max) {
                max = i;
            }
        }

        int max_freq = 0;
        for (int i : times) {
            if (i == max) {
                max_freq++;
            }
        }

        int res = (max - 1) * (n + 1) + max_freq;

        return res > size ? res : size;
    }
};
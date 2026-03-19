#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end(), greater<int>());

        int index = 1;
        for (int x : citations) {
            if (x >= index) {
                index++;
            } else {
                break;
            }
        }

        return index - 1;
    }
};
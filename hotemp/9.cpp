#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0)
            return false;
        else {
            string s = to_string(x);
            int left = 0, right = s.size() - 1;

            while (left < right) {
                if (s[left] != s[right]) {
                    return false;
                }

                left++;
                right--;
            }

            return true;
        }
    }
};
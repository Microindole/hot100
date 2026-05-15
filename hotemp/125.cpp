#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string pureString(string s) {
        int n = s.size();

        int index = 0;
        for (int i = 0; i < n; i++) {
            char ch = s[i];
            if (isalpha(ch)) {
                if (!islower(ch)) {
                    s[index] = s[i] + 32;
                } else {
                    s[index] = s[i];
                }

                index++;
            } else if (isdigit(ch)) {
                s[index] = s[i];
                index++;
            }
        }

        return s.substr(0, index);
    }

    bool isPalindrome(string s) {
        string pure = pureString(s);

        int size = pure.size();
        if (size == 0)
            return true;

        int front = 0, back = size - 1;

        while (front < back) {
            if (pure[front] != pure[back])
                return false;

            front++;
            back--;
        }
        return true;
    }
};
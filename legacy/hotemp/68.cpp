#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int index = 0;
        int n = words.size();
        vector<string> res;
        int tempLetters = 0;

        for (int i = 0; i < n; i++) {
            if (tempLetters + (i - index) + words[i].size() > maxWidth) {
                int numWords = i - index;
                int totalSpaces = maxWidth - tempLetters;

                string s = "";

                if (numWords == 1) {
                    s = words[index] +
                        string(maxWidth - words[index].size(), ' ');

                    index++;

                } else {
                    int perBlank = totalSpaces / (numWords - 1);
                    int rest = totalSpaces % (numWords - 1);

                    while (index < i) {
                        s += words[index];

                        if (index < i - 1) {
                            s += string(perBlank + (rest > 0 ? 1 : 0), ' ');
                            rest--;
                        }
                        index++;
                    }
                }

                res.push_back(s);

                tempLetters = 0;
                i--;
            } else {
                tempLetters += words[i].size();
            }
        }

        string lastLine = "";

        while (index < n) {
            lastLine += words[index];

            if (index < n - 1)
                lastLine += ' ';

            index++;
        }

        if (maxWidth > (int)lastLine.size()) {
            lastLine += string(maxWidth - lastLine.size(), ' ');
        }

        res.push_back(lastLine);

        return res;
    }
};
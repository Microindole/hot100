#include <string>
#include <vector>

std::vector<int> getNext(std::string& p) {
    int size = p.size();
    std::vector<int> next(size);

    next[0] = 0;

    int j = 0;

    for (int i = 1; i < size; i++) {
        while (j > 0 && p[i] != p[j]) {
            j = next[j - 1];
        }

        if (p[i] == p[j]) {
            j++;
        }

        next[i] = j;
    }

    return next;
}

int kmpSearch(std::string s, std::string p) {
    int s_size = s.size(), p_size = p.size();

    std::vector<int> next = getNext(p);

    int j = 0;
    for (int i = 0; i < s_size; i++) {
        while (j > 0 && s[i] != p[j]) {
            j = next[j - 1];
        }

        if (s[i] == p[j]) {
            j++;
        }

        if (j == p_size) {
            return i - p_size + 1;
        }
    }

    return -1;
}

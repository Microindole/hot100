#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Segment {
    string content;
    bool isDigit;
    int val;
};

struct FileNode {
    string originalName;
    vector<Segment> segments;
};

vector<Segment> splitSegments(const string& s) {
    vector<Segment> res;
    int n = s.size();

    for (int i = 0; i < n;) {
        Segment seg;
        int j = i;

        if (isdigit(s[i])) {
            seg.isDigit = true;

            while (j < n && isdigit(s[j])) {
                j++;
            }

            seg.content = s.substr(i, j - i);
            seg.val = stoi(seg.content);
        } else {
            seg.isDigit = false;
            while (j < n && !isdigit(s[j])) j++;
            seg.content = s.substr(i, j - i);
            seg.val = 0;
        }

        res.push_back(seg);
        i = j;
    }

    return res;
}

bool compareFiles(const FileNode& a, const FileNode& b) {
    size_t lenA = a.segments.size();
    size_t lenB = b.segments.size();
    size_t minLen = min(lenA, lenB);

    for (size_t i = 0; i < minLen; ++i) {
        const Segment& segA = a.segments[i];
        const Segment& segB = b.segments[i];

        if (segA.isDigit != segB.isDigit) {
            return segA.isDigit;
        }

        if (segA.isDigit && segB.isDigit) {
            if (segA.val != segB.val) return segA.val < segB.val;

        }

        else {
            if (segA.content != segB.content) return segA.content < segB.content;
        }
    }

    return lenA < lenB;
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<FileNode> files(n);
    for (int i = 0; i < n; ++i) {
        cin >> files[i].originalName;
        files[i].segments = splitSegments(files[i].originalName);
    }

    stable_sort(files.begin(), files.end(), compareFiles);

    for (const auto& f : files) {
        cout << f.originalName << endl;
    }

    return 0;
}
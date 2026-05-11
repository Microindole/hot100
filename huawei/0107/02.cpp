#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    long long x, y;
};

long long getDis(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

long long solve(vector<Point>& ps, int left, int right) {
    long long d = -1;

    if (right - left <= 3) {
        for (int i = left; i <= right; i++) {
            for (int j = i + 1; j <= right; j++) {
                long long temp = getDis(ps[i], ps[j]);
                if (d == -1 || temp < d) {
                    d = temp;
                }
            }
        }
        return d;
    }

    int mid = left + (right - left) / 2;
    long long midx = ps[mid].x;
    long long dl = solve(ps, left, mid);
    long long dr = solve(ps, mid + 1, right);

    d = min(dl, dr);

    vector<Point> during;
    for (int i = left; i <= right; i++) {
        if ((ps[i].x - midx) * (ps[i].x - midx) <= d) {
            during.push_back(ps[i]);
        }
    }

    sort(during.begin(), during.end(),
         [](const Point& a, const Point& b) { return a.y < b.y; });

    for (int i = 0; i < during.size(); i++) {
        for (int j = i + 1;
             j < during.size() &&
             (during[i].y - during[j].y) * (during[i].y - during[j].y) <= d;
             j++) {
            d = min(d, getDis(during[i], during[j]));
        }
    }

    return d;
}

int main() {
    int n;
    cin >> n;

    vector<Point> ps(n);
    for (int i = 0; i < n; i++) {
        cin >> ps[i].x >> ps[i].y;
    }

    sort(ps.begin(), ps.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    cout << solve(ps, 0, n - 1);

    return 0;
}
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, a, b;
    cin >> n >> a >> b;

    long long area = 0;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int left = max(x1, 0), right = min(x2, a);
        int width = right - left;

        int bottom = max(y1, 0), top = min(y2, b);
        int height = top - bottom;

        if (width > 0 && height > 0) {
            area += (long long)width * height;
        }
    }

    cout << area << endl;
}

/*
4 10 10
0 0 5 5
5 -2 15 3
8 8 15 15
-2 10 3 15
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

struct pic {
    long long id, t;
};

struct res {
    long long id, t;
    int timeshow;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_map<long long, long long> picsfun;
    unordered_map<long long, int> times;
    vector<vector<pic>> pics(n);

    cin.ignore();

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);

        stringstream ss(line);
        long long t, id;
        while (ss >> id >> t) {
            pic tempic;
            tempic.t = t;
            tempic.id = id;

            picsfun[id] = t;

            times[id]++;
        }
    }

    vector<res> result;
    for (const auto& tt : times) {
        if (tt.second > 1) {
            res temp;
            temp.id = tt.first;
            temp.t = picsfun[tt.first];
            temp.timeshow = tt.second;
            result.push_back(temp);
        }
    }

    sort(result.begin(), result.end(), [](const res& a, const res& b) { return a.t < b.t; });

    for (res r : result) {
        cout << r.id << " " << r.timeshow << " ";
    }

    return 0;
}
// 64 位输出请用 printf("%lld")
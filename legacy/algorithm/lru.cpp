#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

int cap;
list<int> q;
unordered_map<int, int> val_map;
unordered_map<int, list<int>::iterator> pos_map;

void put(int key, int value) {
    if (val_map.count(key)) {
        q.erase(pos_map[key]);
    } else if (q.size() == cap) {
        int oldKey = q.front();  // 拿到最前面的（最旧的）
        val_map.erase(oldKey);   // 从值表删
        pos_map.erase(oldKey);   // 从书签表删
        q.pop_front();           // 从队列删
    }

    q.push_back(key);
    pos_map[key] = --q.end();
    val_map[key] = value;
}

int get(int key) {
    if (!val_map.count(key)) {
        return -1;
    }

    // int pos = pos_map[key];
    q.erase(pos_map[key]);

    q.push_back(key);

    pos_map[key] = --q.end();

    return val_map[key];
}

int main() {
    int t;
    cin >> t;
    cin >> cap;

    while (t--) {
        string op;
        cin >> op;

        if (op == "put") {
            int key, value;
            cin >> key >> value;

            put(key, value);
        } else if (op == "get") {
            int key;
            cin >> key;

            int res = get(key);

            cout << res << "\n";
        }
    }
}
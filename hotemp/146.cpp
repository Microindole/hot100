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
        int oldKey = q.front();

        val_map.erase(oldKey);
        pos_map.erase(oldKey);

        q.pop_front();
    }

    q.push_back(key);
    val_map[key] = value;
    pos_map[key] = --q.end();
}

int get(int key) {
    if (!val_map.count(key)) {
        return -1;
    }

    q.erase(pos_map[key]);
    q.push_back(key);
    pos_map[key] = --q.end();

    return val_map[key];
}

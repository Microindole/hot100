#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    int cap = 0;
    list<int> q;
    unordered_map<int, int> val;
    unordered_map<int, list<int>::iterator> pos;

public:
    LRUCache(int capacity) { this->cap = capacity; }

    int get(int key) {
        if (!val.count(key))
            return -1;

        q.erase(pos[key]);
        q.push_back(key);
        pos[key] = --q.end();

        return val[key];
    }

    void put(int key, int value) {
        if (val.count(key)) {
            q.erase(pos[key]);
        } else if (q.size() == cap) {
            int front = q.front();

            q.pop_front();
            val.erase(front);
            pos.erase(front);
        }

        q.push_back(key);
        val[key] = value;
        pos[key] = --q.end();
    }
};
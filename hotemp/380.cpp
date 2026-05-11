#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class RandomizedSet {
private:
    vector<int> nums;
    unordered_map<int, int> valToIndex;

public:
    RandomizedSet() {}

    bool insert(int val) {
        if (valToIndex.count(val)) {
            return false;
        }

        valToIndex[val] = nums.size();
        nums.push_back(val);

        return true;
    }

    bool remove(int val) {
        if (!valToIndex.count(val)) {
            return false;
        }

        int index = valToIndex[val];
        int lastElement = nums.back();

        nums[index] = lastElement;
        valToIndex[lastElement] = index;

        nums.pop_back();
        valToIndex.erase(val);

        return true;
    }

    int getRandom() { return nums[rand() % nums.size()]; }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
#include <queue>

using namespace std;

class MedianFinder {
    priority_queue<int> left;  // 大顶，更小，排前面
    priority_queue<int, vector<int>, greater<int>> right;

public:
    MedianFinder() {}

    void addNum(int num) {
        int lsize = left.size(), rsize = right.size();

        if (rsize == 0) {
            right.push(num);
        } else if (lsize == rsize) {
            if (num < left.top()) {
                int temp = left.top();
                right.push(temp);
                left.pop();
                left.push(num);
            } else {
                right.push(num);
            }
        } else {
            if (num > right.top()) {
                int temp = right.top();
                left.push(temp);
                right.pop();
                right.push(num);
            } else {
                left.push(num);
            }
        }
    }

    double findMedian() {
        if (left.size() == right.size()) {
            return (static_cast<double>(left.top()) + right.top()) / 2.0;
        }

        return right.top();
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
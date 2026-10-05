#include <algorithm>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node {
    int capital;
    int profit;
};

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits,
                             vector<int>& capital) {
        int n = capital.size();

        vector<Node> nodes;

        for (int i = 0; i < n; i++) {
            nodes.push_back({capital[i], profits[i]});
        }

        sort(nodes.begin(), nodes.end(), [](const Node& a, const Node& b) {
            if (a.capital == b.capital) {
                return a.profit > b.profit;
            }
            return a.capital < b.capital;
        });

        auto cmp = [](const Node& a, const Node& b) {
            if (a.profit == b.profit) {
                return a.capital > b.capital;
            }

            return a.profit < b.profit;
        };

        priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);

        int index = 0;
        while (k--) {
            while (index < n && nodes[index].capital <= w) {
                pq.push(nodes[index]);
                index++;
            }

            if (pq.empty())
                break;

            w += pq.top().profit;
            pq.pop();
        }

        return w;
    }
};
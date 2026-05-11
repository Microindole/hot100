#include <string>
#include <unordered_map>
#include <vector>

namespace std {

class Solution {
private:
    unordered_map<string, string> parent;
    unordered_map<string, double> weight;

    // 查找根节点，并进行路径压缩
    string find(string i) {
        if (parent[i] != i) {
            string originParent = parent[i];
            parent[i] = find(parent[i]);
            // 更新当前节点到新父节点（根节点）的权重
            weight[i] *= weight[originParent];
        }
        return parent[i];
    }

    // 合并两个节点
    void unite(string i, string j, double value) {
        string rootI = find(i);
        string rootJ = find(j);
        if (rootI != rootJ) {
            parent[rootI] = rootJ;
            // 计算 rootI 到 rootJ 的权重：(i->j) * (j->rootJ) / (i->rootI)
            weight[rootI] = value * weight[j] / weight[i];
        }
    }

public:
    vector<double> calcEquation(vector<vector<string>>& equations,
                                vector<double>& values,
                                vector<vector<string>>& queries) {
        // 初始化并查集
        for (int i = 0; i < equations.size(); ++i) {
            string a = equations[i][0];
            string b = equations[i][1];
            if (parent.find(a) == parent.end()) {
                parent[a] = a;
                weight[a] = 1.0;
            }
            if (parent.find(b) == parent.end()) {
                parent[b] = b;
                weight[b] = 1.0;
            }
            unite(a, b, values[i]);
        }

        vector<double> results;
        for (const auto& q : queries) {
            string a = q[0];
            string b = q[1];

            // 1. 如果变量从未出现过
            if (parent.find(a) == parent.end() ||
                parent.find(b) == parent.end()) {
                results.push_back(-1.0);
            } else {
                string rootA = find(a);
                string rootB = find(b);
                // 2. 如果两个变量不在同一个连通分量中
                if (rootA != rootB) {
                    results.push_back(-1.0);
                } else {
                    // 3. 在同一连通分量，结果即为 weight[a] / weight[b]
                    results.push_back(weight[a] / weight[b]);
                }
            }
        }
        return results;
    }
};

}  // namespace std
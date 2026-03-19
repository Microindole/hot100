#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) { val = _val; }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    // int maxDepth(Node* root) {
    //     if (root == nullptr) {
    //         return 0;
    //     }

    //     int max_depth = 0;

    //     for (Node* node : root->children) {
    //         max_depth = max(max_depth, maxDepth(node));
    //     }

    //     return max_depth + 1;
    // }

    int maxDepth(Node* root) {
        if (root == nullptr) {
            return 0;
        }

        queue<Node*> q;
        q.push(root);

        int depth = 0;

        while (!q.empty()) {
            int size = q.size();

            depth++;

            for (int i = 0; i < size; i++) {
                Node* curr = q.front();
                q.pop();

                for (Node* child : curr->children) {
                    if (child) {
                        q.push(child);
                    }
                }
            }
        }

        return depth;
    }
};
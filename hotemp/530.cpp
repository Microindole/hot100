#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    void getResByInOrder(TreeNode* root, int& front, int& back, int& res, int& count) {
        if (root == nullptr) {
            return;
        }

        if (root->left) {
            getResByInOrder(root->left, front, back, res, count);
        }

        if (count == 0) {
            back = root->val;
            count = 1;
        } else {
            front = back;
            back = root->val;

            res = min(res, back - front);
            count = 2;
        }

        if (root->right) {
            getResByInOrder(root->right, front, back, res, count);
        }
    }

    int getMinimumDifference(TreeNode* root) {
        int front = 0, back = 0;
        int count = 0;
        int res = INT_MAX;

        getResByInOrder(root, front, back, res, count);
        if (count == 2) {
            return res;
        } else {
            return 0;
        }
    }
};
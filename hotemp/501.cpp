#include <iostream>
#include <vector>

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
    vector<int> res;
    int curr = 0, curr_count = 0, max_count = 0;

    void update(int val) {
        if (val == curr) {
            curr_count++;
        } else {
            curr = val;
            curr_count = 1;
        }

        if (curr_count == max_count) {
            res.push_back(val);
        } else if (curr_count > max_count) {
            max_count = curr_count;
            res.clear();

            res.push_back(val);
        }
    }

    void inOrder(TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        inOrder(root->left);
        update(root->val);
        inOrder(root->right);
    }

    vector<int> findMode(TreeNode* root) {
        inOrder(root);
        return res;
    }
};
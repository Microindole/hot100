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
    vector<int> robTree(TreeNode* root) {
        if (root == nullptr) {
            return {0, 0};
        }

        vector<int> left = robTree(root->left), right = robTree(root->right);

        int noRobThis = max(left[0], left[1]) + max(right[0], right[1]);
        int robThis = root->val + left[0] + right[0];

        return {noRobThis, robThis};
    }

    int rob(TreeNode* root) {
        vector<int> res = robTree(root);

        return max(res[0], res[1]);
    }
};
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    int depth(TreeNode* root, int& ans) {
        if (root == nullptr) {
            return 0;
        }

        int leftDepth = depth(root->left, ans);
        int rightDepth = depth(root->right, ans);

        // 经过当前节点的最长路径
        ans = max(ans, leftDepth + rightDepth);

        // 返回当前节点的最大深度
        return max(leftDepth, rightDepth) + 1;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        int ans = 0;
        depth(root, ans);
        return ans;
    }
};
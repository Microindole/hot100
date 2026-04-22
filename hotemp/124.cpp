/**
 * 以每个节点都进行最大路径和的计算，并保留单枝的的最大来源。
 * 使用后续遍历保证不会重复计算
 */
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
    int maxPathSum(TreeNode* root) {
        int maxSum = INT_MIN;
        maxGain(root, maxSum);

        return maxSum;
    }

    int maxGain(TreeNode* root, int& maxSum) {
        if (root == nullptr) {
            return 0;
        }

        int left = max(maxGain(root->left, maxSum), 0);
        int right = max(maxGain(root->right, maxSum), 0);

        int sum = root->val + left + right;

        maxSum = max(maxSum, sum);

        return root->val + max(left, right);
    }
};
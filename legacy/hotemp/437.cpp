#include <unordered_map>

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
    void dfs(TreeNode* root, int targetSum, long long currSum,
             unordered_map<long long, int>& show, int& res) {
        if (root == nullptr) {
            return;
        }

        currSum += root->val;

        if (show.count(currSum - targetSum)) {
            res += show[currSum - targetSum];
        }

        show[currSum]++;

        dfs(root->left, targetSum, currSum, show, res);
        dfs(root->right, targetSum, currSum, show, res);

        show[currSum]--;
    }

    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long long, int> show;
        show[0] = 1;

        int res = 0;
        dfs(root, targetSum, 0, show, res);

        return res;
    }
};
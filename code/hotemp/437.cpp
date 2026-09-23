
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
    void dfs(TreeNode* root, int& targetNum,
             unordered_map<long long, int>& umap, int& res, long long& temp) {
        if (root == nullptr)
            return;

        temp += root->val;
        if (umap.count(temp - targetNum)) {
            res += umap[temp - targetNum];
        }

        umap[temp]++;

        dfs(root->left, targetNum, umap, res, temp);
        dfs(root->right, targetNum, umap, res, temp);

        umap[temp]--;
        temp -= root->val;
    }
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long long, int> umap;

        umap[0] = 1;

        int res = 0;

        long long temp = 0;

        dfs(root, targetSum, umap, res, temp);

        return res;
    }
};
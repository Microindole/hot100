#include <unordered_map>
#include <vector>

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
    TreeNode* build(vector<int>& preorder, vector<int>& inorder,
                    unordered_map<int, int>& umap, int pl, int pr, int il,
                    int ir) {
        if (pl > pr)
            return nullptr;

        int rootVal = preorder[pl];

        TreeNode* root = new TreeNode(rootVal);

        int index = umap[rootVal];

        int lenl = index - il;
        int lenr = ir - index;

        root->left =
            build(preorder, inorder, umap, pl + 1, pl + lenl, il, index - 1);
        root->right =
            build(preorder, inorder, umap, pr - lenr + 1, pr, index + 1, ir);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> umap;

        int n = inorder.size();

        for (int i = 0; i < n; i++) {
            umap[inorder[i]] = i;
        }

        return build(preorder, inorder, umap, 0, n - 1, 0, n - 1);
    }
};
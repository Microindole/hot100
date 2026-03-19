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
    void inorder(TreeNode* root, vector<int>& res) {
        if (root == nullptr) {
            return;
        }

        inorder(root->left, res);

        res.push_back(root->val);

        inorder(root->right, res);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;

        inorder(root, res);

        return res;
    }
};

#include <stack>

class Solution2 {
public:
    /**
     * @brief 使用迭代方式对二叉树进行中序遍历。
     *
     * 中序遍历顺序为：
     * 左子树 -> 根节点 -> 右子树。
     *
     * 该方法使用显式栈模拟递归调用栈：
     * 1. 从当前节点开始不断向左遍历，并将经过的节点压入栈中。
     * 2. 当左子树遍历到底后，弹出栈顶节点并访问。
     * 3. 然后转向该节点的右子树，重复上述过程。
     *
     * @param root 二叉树根节点指针。
     * @return vector<int> 按中序遍历顺序得到的节点值数组。
     *
     * @complexity
     * - 时间复杂度: O(n)，每个节点最多入栈和出栈各一次。
     * - 空间复杂度: O(h)，其中 h 为二叉树高度。
     *   最坏情况下树退化为链表，空间复杂度为 O(n)；
     *   平衡二叉树情况下约为 O(log n)。
     */
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> st;
        TreeNode* cur = root;

        while (cur != nullptr || !st.empty()) {
            // 不断向左遍历，并保存沿途节点
            while (cur != nullptr) {
                st.push(cur);
                cur = cur->left;
            }

            // 左子树遍历完成，访问当前根节点
            cur = st.top();
            st.pop();

            res.push_back(cur->val);

            // 接下来遍历右子树
            cur = cur->right;
        }

        return res;
    }
};

int main() {}